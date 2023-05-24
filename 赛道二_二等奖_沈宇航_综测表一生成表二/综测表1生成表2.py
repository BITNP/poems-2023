import json
import os
import queue
import threading
import tkinter.filedialog as tf
import traceback
from tkinter import Entry

import numpy as np
import pandas as pd
import requests
import ttkbootstrap as tk
import ttkbootstrap.scrolled as ts
from ttkbootstrap import Button, Label, StringVar
from ttkbootstrap.constants import *
from ttkbootstrap.dialogs.dialogs import Messagebox as tm

"""
    睿信综测表格生成
    @author Shen
    @date 2022-03-10
          2022-09-10 : GUI页面，修复部分bug

    根据综测详细表格生成个人汇总，建议您自行核对数据是否有误！
    数据转换有问题导致的后果本人不负责任
"""
# 原文件地址
FILE_PATH = r""
# 新文件地址（默认与源文件同一文件夹）
NEW_FILE_PATH = os.path.join(os.path.dirname(FILE_PATH), "生成的表格.xlsx")
VERSION = 1


def part(name: str):
    def dec(func):
        def wrapper(*args, **kwargs):
            try:
                send_message(f"正在处理{name}...")
                r = func(*args, **kwargs)
                send_message(f"{name}处理完成！")
                return r
            except Exception as e:
                print(f"处理{name}时出现异常！"+traceback.format_exc())
        return wrapper
    return dec


@part("b1")
def process_b1(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=4))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[4].strftime("%Y年%m月%d日"))
        name = line[6]
        name = name[:name.index("（")]
        infos.append(name)
        infos.append(line[8].replace(" ", ""))
        evidence = line[11]
        infos.append("无证明" if evidence == "尚未开出证明" else "有证明")
        infos.append(f"{line[10]}分")
        text.append("，".join(infos))
    result = ""
    for i, t in enumerate(text):
        result += f"{i+1}、{t}\n"
    return result


@part("b2_科创活动")
def process_b2(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=6))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[3].strftime("%Y年%m月%d日"))
        infos.append(line[4])
        name = line[6]
        if "（" in name:
            name = name[:name.index("（")]
        infos.append(name)
        author = line[9]
        author = author[:author.index("/")]
        infos.append(author)
        evidence = line[11]
        infos.append("无证明" if evidence == "尚未开出证明" else "有证明")
        infos.append(f"{line[12]}分")
        text.append("，".join(infos))
    return text


@part("b2_学术成果")
def process_b2_2(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=4))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[4].strftime("%Y年%m月%d日"))
        # infos.append(line[4])
        name = line[6]
        name = name[:name.index("/")]
        infos.append(name)
        author = line[9]
        author = author[:author.index("/")]
        infos.append(author)
        evidence = line[11]
        infos.append("无证明" if evidence == "尚未开出证明" else "有证明")
        infos.append(f"{line[12]}分")
        text.append("，".join(infos))
    return text


@part("c1")
def process_c1(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=4))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[8])
        infos.append(line[4].strftime("%Y年%m月"))
        evidence = line[11]
        infos.append("无证明" if evidence == "尚未开出证明" else "有证明")
        infos.append(f"{line[9]}分")
        text.append("，".join(infos))
    return arr_to_text(text)


@part("c2")
def process_c2(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=5))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[4].strftime("%Y年%m月"))
        name = line[5]
        name = name[:name.index("/")]
        infos.append(name)
        infos.append(line[7].replace("，", ""))
        evidence = line[11]
        infos.append("无证明" if evidence == "尚未开出证明" else "有证明")
        infos.append(f"{line[12]}分")
        text.append("，".join(infos))
    return arr_to_text(text)


@part("c3")
def process_c3(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=5))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[4].strftime("%Y年%m月"))
        name = line[6]
        name = name[:name.index("/")]
        infos.append(name+"参赛")
        infos.append(line[7].replace("，", ""))
        evidence = line[11]
        infos.append(evidence if evidence == "尚未开出证明" else "有证明")
        infos.append(f"参与分{line[5]}分")
        infos.append(f"获奖分{line[10]}分")
        infos.append(f"单项总分{line[12]}分")
        text.append("，".join(infos))
    return arr_to_text(text)


@part("c4")
def process_c4(df_sub: pd.DataFrame):
    arr = np.array(df_sub.dropna(thresh=4))
    text = []
    for line in arr:
        infos = []
        if not line[2]:
            continue
        infos.append(line[2])
        infos.append(line[5].strftime("%Y年%m月"))
        infos.append(f"{line[7]}小时")
        evidence = line[11]
        infos.append(evidence if evidence == "尚未开出证明" else "有证明")
        infos.append(f"{line[9]}分")
        text.append("，".join(infos))
    return arr_to_text(text)


def arr_to_text(text):
    result = ""
    for i, t in enumerate(text):
        result += f"{i+1}、{t}\n"
    return result


def check_update():
    url = "https://api.shen2183.cn/zongce/check_update"
    try:
        r = requests.post(url, data={
            "version_code": VERSION,
        })

        if r.status_code == 200:
            print(r.text)
            d = json.loads(r.text)
            if d.get("should_update", False):
                v = d.get("version_code", "未知版本")
                send_message(
                    f"检测到有新版本v{v}，更新内容：\n{d.get('update_message', '无')}\n请点击链接 {d.get('url', '无')} 下载")
            else:
                send_message("更新检查完成，已是最新版本")
    except Exception as e:
        send_message(f"检查更新失败：{e}")


class ReText(queue.Queue):
    def __init__(self):
        queue.Queue.__init__(self)

    def write(self, content):
        self.put(content)


msg_queue = ReText()


def send_message(msg):
    msg_queue.put(msg)


def update_message():
    while not msg_queue.empty():
        content = msg_queue.get()
        print(content)
        label_title.insert(tk.END, f"{content}\n")
    root.after(100, update_message)


def main():
    df = None
    try:
        df = pd.read_excel(FILE_PATH)
    except Exception as e:
        send_message("读取原表格失败，请检查文件路径并确保没有其他程序占用此文件！")
        print(e)
        return
    else:
        send_message("读取原表格成功！")

    values = {
        "姓名": "",
        "学号": "",
        "书院年级": "",
        "行政班级": "",
        "辅导员": var_fdy.get(),
        "专业": "",
        "参与分B1": "",
        "B1总分": "",
        "参与分B2": "",
        "B2总分": "",
        "参与分C1": "",
        "C1总分": "",
        "参与分C2": "",
        "C2总分": "",
        "参与分C3": "",
        "C3总分": "",
        "参与分C4": "",
        "C4总分": ""
    }
    values["姓名"] = df.iloc[1, 10]
    values["学号"] = str(df.iloc[1, 13])
    values["书院年级"] = df.iloc[1, 2]
    values["行政班级"] = df.iloc[1, 4]
    values["专业"] = df.iloc[1, 7]
    values["参与分B1"] = process_b1(df.iloc[4:12, ])
    values["参与分B2"] = arr_to_text(process_b2(
        df.iloc[13:18, ])+process_b2_2(df.iloc[19:22, :]))
    values["参与分C1"] = process_c1(df.iloc[23:27, ])
    values["参与分C2"] = process_c2(df.iloc[28:33, ])
    values["参与分C3"] = process_c3(df.iloc[34:49, ])
    values["参与分C4"] = process_c4(df.iloc[50:57, ])
    values["B1总分"] = df.iloc[4, 12]
    values["B2总分"] = df.iloc[13, 13]
    values["C1总分"] = df.iloc[23, 12]
    values["C2总分"] = df.iloc[28, 13]
    values["C3总分"] = df.iloc[34, 13]
    values["C4总分"] = df.iloc[50, 12]

    for key in values:
        values[key] = [values[key]]

    new_df = pd.DataFrame(values)
    NEW_FILE_PATH = var_save_file.get()
    new_df.to_excel(NEW_FILE_PATH, index=range(len(values)))
    send_message("生成文件成功，请自行核对各项细节！")
    send_message("粘贴时请选择性粘贴，仅需保留值")
    send_message(f"文件位置: {NEW_FILE_PATH}")


def choose_file_path():
    global FILE_PATH
    FILE_PATH = tf.askopenfilename(filetypes=[("Excel", "*.xlsx")])
    var_source_file.set(FILE_PATH)
    var_save_file.set(FILE_PATH.replace(".xlsx", "_result.xlsx"))


def command_button_start():
    t = threading.Thread(target=main)
    t.start()


if __name__ == "__main__":
    root = tk.Window("睿信综测表1生成表2", themename="litera")
    label_save_path = Label(root, text="请选择表一：")
    label_save_path.grid(row=1, column=0, sticky=E)
    var_source_file = StringVar()
    var_source_file.set("未选择")
    label_file_path = Label(root, textvariable=var_source_file, wraplength=700)
    label_file_path.grid(row=1, column=1, sticky=W+E, columnspan=4)

    button_choose_path = Button(root, text="选择", command=choose_file_path)
    button_choose_path.grid(row=1, column=4, sticky="e",
                            columnspan=1, padx=8, pady=4)

    label_file_name = Label(root, text="生成路径：")
    label_file_name.grid(row=2, column=0, sticky=E, padx=8, pady=4)
    var_save_file = StringVar()
    var_save_file.set("D:/综测表2.xlsx")
    label_path = Entry(root, textvariable=var_save_file)
    label_path.grid(row=2, column=1, sticky="we", columnspan=4)

    label_fdy = Label(root, text="辅导员：")
    label_fdy.grid(row=3, column=0, sticky=E, padx=8, pady=4)
    var_fdy = StringVar()
    var_fdy.set("李婉莹")
    label_fdy = Entry(root, textvariable=var_fdy)
    label_fdy.grid(row=3, column=1, sticky="we", columnspan=4)

    button_start = Button(root, text="开始", command=command_button_start)
    button_start.grid(row=4, column=0, columnspan=5,
                      sticky=E+W, padx=8, pady=4)

    var_title = StringVar()
    label_title = ts.ScrolledText(root)
    label_title.grid(row=5, column=0, columnspan=5)

    root.after(100, lambda: send_message(
        f"欢迎使用睿信综测表格生成器~\n作者：睿信2047 Shen\n当前版本：v{VERSION}"))
    update_message()
    check_update()

    root.mainloop()
