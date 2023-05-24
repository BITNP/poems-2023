# 贡献者指南

## ℹ️ 场地预约概况

我校存在两套系统，[北京书院社区](https://i.bit.edu.cn/EIP/nonlogin/onewebsitehande/toPersonalCenterPage.htm)一套，其它一套。

后一套系统又存在两套前端。

- [桌面版`cdyy`](http://stu.bit.edu.cn/xsfw/sys/cdyyapp/*default/index.do)：[学生综合数据平台](http://stu.bit.edu.cn) → 场地预约，或在[智慧北理统一门户](https://i.bit.edu.cn/EIP/nonlogin/onewebsitehande/toPersonalCenterPage.htm)搜索。

  这套系统会一次性显示所有场地每个时段的预约情况，但服务器响应很慢。

- [i北理移动版`swmcdyy`](http://stu.bit.edu.cn/xsfw/sys/swmcdyyapp/*default/index.do)：i北理 → 场地预约。

  这套系统只会显示每个场地“可预约/满预约”，单击进去后才显示具体时段。不过响应很快。

## 🛠️ 开发

使用 [pdm](https://pdm.fming.dev/) 辅助开发。

```shell
$ pdm install
```

```shell
$ pipx install pre-commit  # Alternate: python -m pip install pre-commit
$ pre-commit install
$ pdm run lint
```
