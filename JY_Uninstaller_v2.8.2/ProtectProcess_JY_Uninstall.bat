echo off
:start
tasklist|findstr /i "JY_Uninstaller_v2.8.2"
if %errorlevel%==0 (
echo "找到！"
) else (
echo "无法找到进程，可能已经被结束，正在尝试重启"
start Killed_msg.vbs
start C:\Users\邹昀轩\Desktop\JY_uninstaller_main\JY_Uninstaller_v2.8.2\JY_Uninstaller_v2.8.2\x64\Debug\JY_Uninstaller_v2.8.2.exe
exit
)
goto start
