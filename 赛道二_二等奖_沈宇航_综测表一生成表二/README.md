# 简介

睿信书院每年的综测填写，都需要填写表一和表二两个表，其中表二是汇总表，内容来自表一。每次填写不免繁琐，因此开发这个小软件，自动根据表一内容生成表二，手动粘贴即可快速完成填写。

软件整体使用 Python，基于 pandas 完成表格内容的解析与生成，基于 tkinter 完成页面制作并使用 ttkbootstrap 进行美化。软件还另有一个后端，部署在服务器以完成版本检测与更新。为了方便使用，基于 pyinstaller 完成了打包，可直接下载后运行在 win10 及以上系统中。