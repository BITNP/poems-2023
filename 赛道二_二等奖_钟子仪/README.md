<p align="center">
  <img src="https://github.com/KJH-x/Batch_Collections/blob/main/Campus_network/Network_Alive.ico" alt="Icon">
</p>

# 校园网脚本食用方法

## 使用步骤

1. 安装[python](https://www.python.org/downloads/)和python依赖：

    > ```batch
    > pip install requests
    > pip install pillow
    > pip install pystray
    > ```

2. 下载[`Campus_network.7z`](https://github.com/KJH-x/Batch_Collections/blob/main/Campus_network/Campus_network.7z)并解压

    > 可选的步骤：检查文件数量是否正确
    >
    > - AIO_login.py
    > - Network_Alive.ico
    > - Network_Alive.py
    > - Readme.md(本文件)
    > - Tray_Launcher.pyw(运行此文件)
    >

3. 运行脚本
    - 开始自动重连：
        1. 双击运行Tray_Launcher.pyw
        2. 按照提示输入账号密码
        3. 挂机
        4. 通过在任务栏托盘处找到图标，右键切换控制台现实情况
    - 只想用来登录、登出（命令行）
        1. `python .\AIO_login.py -a 登录`（或‘登出’）
        2. 按照提示输入账号密码

## 运行截图

<img width="674" alt="截图_20230225232209" src="https://user-images.githubusercontent.com/53437291/221365173-5b283882-f14e-444a-8bd4-947ce5e81e31.png">

## 冷知识

1. 参数：
    - AIO的启动参数暂时只有-a/--action
    - 这个参数可选字段有`login`, `登录`, `登陆`, `上线`, `logout`, `登出`, `下线`, `退出`
2. 脚本故事
    - 本脚本依据模组10_0_0_55版本混合改编（2022），其最新版名称是[bitsrun](https://github.com/BITNP/bitsrun)
    - 缩编为AIO的初衷是减少调用错误，原模组很多bug，外部调用依托答辩，于是缩编
    - 而10_0_0_55模组的祖先是[Aloxaf](https://github.com/Aloxaf/10_0_0_55_login)
    - 一开始我写这个是为了自己和几位朋友用（b校园网老是断联）
    - 在2022下半年测试时发现校园网下ping百度失败的概率比ping哔哩哔哩的失败概率高，故此脚本选择了后者
3. 安全
    - 密码是在本地明文储存的`.\bit_user_detail.json`
    - 由`.\AIO-login.py`在初次使用时创建（或在密码错误等情况下修改）
    - 你可以随时删除，并在下一次登陆的时候重新输入账号密码
    - 注意，自动重连依赖于账号密码的保存

4. 因为身边没有用macos/linux的，也没有经验，故不确定是否支持
5. 欢迎Issue可能的bug
6. 感谢网协某位同学提供的 `pystray` 思路
7. 感谢ChatGPT(March 14 version)的部分代码建议
8. 本代码参加了北京理工大学第一届“十行代码”挑战赛
