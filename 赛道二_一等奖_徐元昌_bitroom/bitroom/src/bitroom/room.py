from __future__ import annotations

import datetime
from asyncio import gather
from dataclasses import asdict, dataclass
from itertools import chain
from json import dumps
from math import ceil
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from typing import Generator

    from httpx import AsyncClient, Response

API_BASE = "http://stu.bit.edu.cn"


async def prepare_headers(client: AsyncClient) -> None:
    """准备请求头

    设置 cookie 等。
    """

    # Get cookie
    res = await client.get(
        f"{API_BASE}/xsfw/sys/swpubapp/indexmenu/getAppConfig.do?appId=4974886768205231&appName=cdyyapp",
        follow_redirects=True,
    )
    res.raise_for_status()

    client.headers.update(
        {
            "Referer": f"{API_BASE}/xsfw/sys/cdyyapp/*default/index.do",
        }
    )


def parse_time_range(time_range: str) -> tuple[datetime.time, datetime.time]:
    """解释时间区间

    # 例子

    ```
    from datetime import time

    assert parse_time_range('08:00-08:45') == (time(8, 0), time(8, 45))
    ```
    """

    parts = time_range.split("-")
    assert len(parts) == 2, f"Invalid time range: “{time_range}”"
    return tuple(datetime.time.fromisoformat(t) for t in parts)


def format_datetime_range(time: tuple[datetime.datetime, datetime.datetime]) -> str:
    """格式化时间区间"""

    if time[0].date() == time[1].date():
        return (
            time[0].isoformat(sep=" ", timespec="minutes")
            + "–"
            + time[1].time().isoformat(timespec="minutes")
        )
    else:
        return "–".join(t.isoformat(sep=" ", timespec="minutes") for t in time)


@dataclass
class Booking:
    """可预约的时空区间"""

    room_name: str
    room_id: str
    t_start: datetime.datetime
    """开始时刻"""
    t_end: datetime.datetime
    """结束时刻"""

    def __str__(self) -> str:
        return (
            f"<Booking [{self.room_name}] "
            f"{format_datetime_range((self.t_start,self.t_end))}>"
        )

    def as_dict(self) -> dict[str, str]:
        raw = asdict(self)
        for k, v in raw.items():
            if isinstance(v, datetime.datetime):
                raw[k] = v.isoformat()

        return raw

    @classmethod
    def from_dict(cls, raw: dict[str, str | datetime.datetime]) -> Booking:
        for k, v in raw.items():
            if k.startswith("t_") and isinstance(v, str):
                raw[k] = datetime.datetime.fromisoformat(v)

        return Booking(**raw)


class RoomAPI:
    """场地预约 API 包装

    ## 例子

    ```
    from datetime import date

    api = await RoomAPI.build(client)
    bookings = await api.get_bookings(date.today())
    ```
    """

    _client: AsyncClient

    @classmethod
    async def build(cls, client: AsyncClient) -> RoomAPI:
        """
        :param client: 已登录的 client，用于后续所有网络请求（会被修改）
        """

        await prepare_headers(client)
        return RoomAPI(client)

    def __init__(self, client: AsyncClient) -> None:
        """
        请使用`build`。
        """

        self._client = client

    async def _post(self, url_path: str, **kwargs) -> Response:
        return await self._client.post(
            f"{API_BASE}{url_path}",
            **kwargs,
        )

    async def _fetch_data(
        self, date: datetime.date, page: int, *, rooms_per_page: int
    ) -> dict:
        """Get a page of data
        :param date: 日期
        :param page: 第几页，从0开始
        :param rooms_per_page: 每页房间数量
        :return: 相邻一周（周一–周日）的预约情况
        """

        res = await self._post(
            "/xsfw/sys/cdyyapp/modules/CdyyApplyController/getSiteInfo.do",
            data={
                "data": dumps(
                    {
                        # 预约日期
                        "YYRQ": date.isoformat(),
                        "pageNumber": page + 1,
                        "pageSize": rooms_per_page,
                    }
                )
            },
            timeout=max(20, 20 * rooms_per_page),  # Yes, it's really slow…
            follow_redirects=True,
        )
        res.raise_for_status()
        json = res.json()
        assert json["code"] == "0" and json["msg"] == "成功"

        return json["data"]

    def _parse_data(
        self, data: dict, *, dates: list[datetime.date]
    ) -> Generator[Booking, None, None]:
        """Parse a page of data to bookings
        :param data: API 的原始响应
        :param dates: 涉及的日期，周一–周日
        """

        # 每个房间
        for room in data["siteInfoList"]:
            # 每一天
            for date_status in room["currentWeekData"]:
                if date_status["isLock"] or date_status["applyTime"] == "":
                    continue

                # 每个时段
                for time_range in date_status["applyTime"].split(","):
                    t_start, t_end = (
                        datetime.datetime.combine(dates[date_status["XQJ"] - 1], t)
                        for t in parse_time_range(time_range)
                    )
                    yield Booking(
                        room_name=room["CDMC"],
                        room_id=room["CDDM"],
                        t_start=t_start,
                        t_end=t_end,
                    )

    async def _fetch_bookings_page(
        self,
        page: int,
        *,
        date: datetime.date,
        rooms_per_page: int,
        dates: list[datetime.date],
    ) -> list[Booking]:
        """Fetch a page of bookings

        :param date: 日期
        :param page: 第几页，从0开始
        :param rooms_per_page: 每页房间数量
        :param dates: 涉及的日期，周一–周日
        """

        data = await self._fetch_data(date, page=page, rooms_per_page=rooms_per_page)
        return list(self._parse_data(data, dates=dates))

    async def fetch_bookings(
        self, date: datetime.date, *, rooms_per_page=3
    ) -> list[Booking]:
        """获取可预约的时空区间

        :param date: 日期
        :param rooms_per_page: 访问 API 时每页房间数量
        :yield: 相邻一周（周一–周日）可预约的时空区间

        # 玄学

        响应时间与 rooms_per_page 近似线性正相关。

        若不并发，rooms_per_page=10 时单位时间获取的房间最多。
        """

        # 首先试探，取得基本数据
        # 只获取一项响应更快
        sniff_data = await self._fetch_data(date, page=0, rooms_per_page=1)

        dates = [date.fromisoformat(it["WEEKDATE"]) for it in sniff_data["weekList"]]
        """此次查询涉及的日期，周一–周日"""

        n_rooms = int(sniff_data["siteInfoList"][0]["totalCount"])
        n_pages = ceil(n_rooms / rooms_per_page)

        # 然后获取所有数据
        # 每一页的结果
        bookings_set = await gather(
            *(
                self._fetch_bookings_page(
                    page=p, date=date, rooms_per_page=rooms_per_page, dates=dates
                )
                for p in range(n_pages)
            )
        )

        # Flatten
        return list(chain.from_iterable(bookings_set))
