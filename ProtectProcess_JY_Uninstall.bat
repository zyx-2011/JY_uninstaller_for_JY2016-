echo off
:start
tasklist|findstr /i "JY_uninstaller_v2.8.1.exe"
if %errorlevel%==0 (
echo "�ҵ���"
) else (
echo "�޷��ҵ����̣������Ѿ������������ڳ�������"
start Killed_msg.vbs
start JY_uninstaller_v2.8.1.exe
exit
)
goto start
