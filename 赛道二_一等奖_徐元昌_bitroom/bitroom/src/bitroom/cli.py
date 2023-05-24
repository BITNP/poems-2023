from asyncio import run
from datetime import date
from json import dumps, load
from sys import exit, stdin

import click
from httpx import AsyncClient

from . import Booking, RoomAPI, auth
from .config import Config, read_config
from .config import config_paths as _config_paths


@click.group()
@click.version_option()
def cli() -> None:
    """BIT 场地预约查询接口"""
    pass


@cli.command()
def config_paths() -> None:
    """列出配置文件可能的位置"""
    click.echo("\n".join(map(str, _config_paths())))


async def _show(config: Config) -> list[Booking]:
    async with AsyncClient() as client:
        await auth(client, config.username, config.password)
        api = await RoomAPI.build(client)

        return await api.fetch_bookings(date.today())


@cli.command()
@click.option("--json/--no-json", default=False, help="按 JSON 格式输出")
@click.option(
    "--auth",
    type=str,
    help="认证信息，形如“1120771210:cyberpunk”（<学号>:<密码>）；不建议使用，请改用配置文件",
)
def show(json: bool, auth: str | None):
    """显示所有可预约的时空区间

    默认从 API 爬取，因服务器响应慢，大约需 10 s。

        $ bitroom show

    也可直接从 stdin 提供之前的结果。

    \b
        $ bitroom show --json > ./bookings.json
        $ cat ./bookings.json | bitroom show
    """

    config = read_config()
    if auth is not None:
        click.echo(
            f"{click.style('[Warning]', fg='yellow')} "
            "不建议使用 --auth，这会让密码出现在命令行历史记录中，更容易泄露。"
            "请改用配置文件。"
        )

        username, password = auth.split(":", maxsplit=1)
        if config is None:
            config = Config(username, password)
        else:
            config.username = username
            config.password = password

    # If stdin is empty, fetch bookings from API.
    # Otherwise, take stdin.
    if stdin.isatty():
        if config is None:
            click.echo(
                f"{click.style('[Error]', fg='red')} "
                "未提供学号、密码，将无法认证。请填写配置文件。"
                "可用 bitroom config-paths 查看文件位置。"
            )
            exit(1)

        bookings = run(_show(config))
    else:
        bookings = map(Booking.from_dict, load(stdin))

    if json:
        click.echo(dumps([b.as_dict() for b in bookings]))
    else:
        click.echo("\n".join(map(str, bookings)))
