echo off
:start
tasklist|findstr /i "JY_uninstaller_v2.8.2.exe"
if %errorlevel%==0 (
echo "找到！"
) else (
echo "无法找到进程，可能已经被结束，正在尝试重启"
start Killed_msg.vbs
start JY_uninstaller_v2.8.2.exe
exit
)
goto start
