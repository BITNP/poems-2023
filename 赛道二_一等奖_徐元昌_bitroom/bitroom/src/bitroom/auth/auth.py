"""
Modified from BIT_leave.
https://github.com/YoungKlaus/BIT_Auto_Leave/blob/895c0bdc7a9d111bdf4230e4e4102e2c51573255/BIT_leave.py
"""

from __future__ import annotations

import re
from typing import TYPE_CHECKING

from execjs import compile

from .encrypt_js import encrypt_js

if TYPE_CHECKING:
    from httpx import AsyncClient


def encrypt(password: str, salt: str) -> str:
    """给密码加盐"""
    context = compile(encrypt_js)
    return context.call("encryptPassword", password, salt)


async def auth(client: AsyncClient, username: str, password: str) -> None:
    """登录账号

    登录失败则抛出异常。

    # 例子

    ```
    from httpx import AsyncClient

    from auth import auth

    async with AsyncClient() as client:
        await auth(client, username="1120771210", password="cyberpunk")
    ```
    """

    login_url = "https://login.bit.edu.cn/authserver/login"
    headers = {
        # ruff: noqa: E501
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
        "Accept-Language": "zh-CN,zh;q=0.9",
        "Proxy-Connection": "keep-alive",
        "Upgrade-Insecure-Requests": "1",
        # ruff: noqa: E501
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36",
        "Referer": "https://login.bit.edu.cn/authserver/login",
    }
    get_login = await client.get(login_url)
    get_login.encoding = "utf-8"
    salt = re.search('id="pwdEncryptSalt" value="(.*?)"', get_login.text).group(1)
    execution = re.search('name="execution" value="(.*?)"', get_login.text).group(1)

    personal_info = {
        "username": username,
        "password": encrypt(password, salt),
        "_eventId": "submit",
        "cllt": "userNameLogin",
        "dllt": "generalLogin",
        "lt": None,
        # 'captcha': None,
        "execution": execution,
    }

    res = await client.post(url=login_url, headers=headers, data=personal_info)
    res.encoding = "utf-8"

    if res.is_success or "二维码扫码登录" in res.text:
        # 登录失败了，检查原因

        match = re.search(
            r'<span id="showErrorTip"><span>(?P<reason>.+)</span></span>', res.text
        )
        reason = match.group("reason") if match else "未知错误"
        raise Exception(f"登录失败：{reason}")
