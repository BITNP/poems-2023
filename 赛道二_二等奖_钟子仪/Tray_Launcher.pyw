import pystray
import win32gui
import win32con
import win32process
import subprocess
import os
import sys
from PIL import Image
import ctypes
import time


def toggle_window_visibility(process: subprocess.Popen):
    """
    Toggles the visibility of a window by its handle.
    """
    handle = get_window_by_pid(process)
    if win32gui.IsWindowVisible(handle):
        # Window is visible, hide it
        win32gui.ShowWindow(handle, win32con.HIDE_WINDOW)
    else:
        win32gui.ShowWindow(handle, win32con.SHOW_OPENWINDOW)


def get_window_by_pid(process: subprocess.Popen) -> int:
    window = 0
    windows = []

    def enum_windows_callback(hWnd: int, lParam):
        if win32process.GetWindowThreadProcessId(hWnd)[1] == process.pid:
            windows.append(hWnd)
    win32gui.EnumWindows(enum_windows_callback, None)
    if len(windows) > 0:
        # If multiple windows are found with the same PID, just use the first one
        window = windows[0]
        # Return Handle
        return window

    else:
        return 0


def on_tray_click(process: subprocess.Popen):
    """
    Callback function that is called when the tray icon is clicked.
    """
    toggle_window_visibility(process)


def create_tray_icon(process: subprocess.Popen):
    """
    Creates a system tray icon using pystray.
    """
    icon_image = Image.open(".\\Network_Alive.ico")
    tray_instance = pystray.Icon('双击显示/隐藏程序框，右键功能菜单', icon_image, title="自动重登 By KJH-x")
    tray_instance.menu = pystray.Menu(
        pystray.MenuItem('显示/隐藏', lambda: on_tray_click(process)),
        pystray.MenuItem('退出', lambda: terminate_program(
            process, tray_instance))
    )
    # tray_instance.title("自动重登")
    ctypes.windll.shcore.SetProcessDpiAwareness(True)
    tray_instance.run()


def terminate_program(process: subprocess.Popen, tray_instance: pystray.Icon):
    process.kill()
    tray_instance.stop()


if __name__ == '__main__':
    os.chdir(sys.path[0])

    Network_Alive = subprocess.Popen(
        "python .\\Network_Alive.py",
        creationflags=subprocess.CREATE_NEW_CONSOLE
    )

    if os.path.exists(".\\bit_user_detail.json"):
        time.sleep(1)
        toggle_window_visibility(Network_Alive)

    create_tray_icon(Network_Alive)
