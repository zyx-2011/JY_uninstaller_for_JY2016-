echo off
:start
tasklist|findstr /i "JY_Uninstaller_v2.8.2"
if %errorlevel%==0 (
echo "�ҵ���"
) else (
echo "�޷��ҵ����̣������Ѿ������������ڳ�������"
start Killed_msg.vbs
start C:\Users\������\Desktop\JY_uninstaller_main\JY_Uninstaller_v2.8.2\JY_Uninstaller_v2.8.2\x64\Debug\JY_Uninstaller_v2.8.2.exe
exit
)
goto start
