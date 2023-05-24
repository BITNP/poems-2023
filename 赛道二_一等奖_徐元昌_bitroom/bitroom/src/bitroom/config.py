"""
Inspired by bitsrun.
https://github.com/YoungKlaus/BIT_Auto_Leave/blob/895c0bdc7a9d111bdf4230e4e4102e2c51573255/BIT_leave.py
(WTFPL license)
"""

from __future__ import annotations

from dataclasses import dataclass
from os import getenv
from pathlib import Path
from sys import platform, version_info
from typing import TYPE_CHECKING

from platformdirs import site_config_path, user_config_path
from platformdirs.unix import Unix

if version_info >= (3, 11):
    from tomllib import loads
else:
    from tomli import loads


if TYPE_CHECKING:
    from typing import Generator

_APP_NAME = "bitroom"


def config_paths() -> Generator[Path, None, None]:
    """配置文件路径

    按优先顺序一一 yield 路径
    """

    if path_from_env := getenv(f"{_APP_NAME}_config_path".upper()):
        yield Path(path_from_env)

    filename = "config.toml"

    yield user_config_path(_APP_NAME, appauthor=False, roaming=True) / filename
    yield site_config_path(_APP_NAME, appauthor=False) / filename

    if platform.startswith("darwin"):
        # Many macOS users think that's a Unix distro.
        dirs = Unix(_APP_NAME, appauthor=False, roaming=True)
        yield dirs.user_config_path / filename
        yield dirs.site_config_path / filename


@dataclass
class Config:
    username: str
    password: str


def read_config() -> Config | None:
    """读取配置文件

    - 有正常配置，返回配置
    - 文件存在但内容不合法，异常
    - 不存在文件，无返回
    """

    for path in config_paths():
        if path.exists():
            return Config(**loads(path.read_text(encoding="utf-8")))
