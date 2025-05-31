#include<iostream>
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#include <conio.h>

using namespace std;

static void setColor(int color) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}
static void print_info() {
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "[Info]";
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
static void print_warn() {
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << "[Warn]";
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
static void print_err() {
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << "[Error]";
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
static bool write_preventkill() {
    fstream file1;
    file1.open("ProtectProcess_JY_Uninstall.bat", ios::out);
    if (file1) {
        file1 << "echo off" << endl;
        file1 << ":start" << endl;
        file1 << "tasklist|findstr /i \"JY_uninstaller_v2.8.1.exe\"" << endl;
        file1 << "if %errorlevel%==0 (" << endl;
        file1 << "echo \"找到！\"" << endl;
        file1 << ") else (" << endl;
        file1 << "echo \"无法找到进程，可能已经被结束，正在尝试重启\"" << endl;
        file1 << "start Killed_msg.vbs" << endl;
        file1 << "start JY_uninstaller_v2.8.1.exe" << endl;
        file1 << "exit" << endl;
        file1 << ")" << endl;
        file1 << "goto start" << endl;
        return true;
    }
    else {
        return false;
    }
}
static bool write_msgvbs() {
    fstream file2;
    file2.open("Killed_msg.vbs", ios::out);
    if (file2) {
        file2 << "dim answer" << endl;
        file2 << "answer=MsgBox(\"无法找到主程序进程，可能已经被结束，正在尝试重启\",16,\"ERROR:主程序被结束\")" << endl;
        return true;
    }
    else {
        return false;
    }
}
int main() {
    begin_main_into:
    system("title 极域卸载工具    v2.8.1(控制台版)");
    fstream file;
    file.open("Running_Time.tmp", ios::in);
    if (!file) {
    mzsm:
        cout << "免责声明：您使用该程序对南京极域信息科技有限公司和学校机房造成的任何损害由您自行承担，与原开发者无关" << endl;
        cout << "本软件仅供学习使用,遵从Apache License2.0协议,但不代表您可以越过您所在地区的法律,一切后果由您自行承担" << endl;
        cout << "Github仓库地址:https://github.com/zyx-2011/JY_uninstaller_for_JY2016-/upload/main" << endl;
        cout << "如果您同意，请输入y,不同意请输入n，程序将会退出：";
        char mz;
        cin >> mz;
        if (mz == 'y' || mz == 'Y') {
            file.open("Running_Time.tmp", ios::out);
            if (file) {
                file << "\"Accept\":\"true\"" << endl;
            }
            else {
                print_warn();
                cout << "写入文件错误，下次可能需要再次同意!" << endl;
                Sleep(1000);
            }
            system("cls");
            goto begin_main_into;
        }
        else if (mz == 'n' || mz == 'N') {
            return 0;
        }
        else {
            cout << "您的输入有误，请重新输入" << endl;
            Sleep(1000);
            system("cls");
            goto mzsm;
        }

    }
    const int MAXPATH = 250;
    char buffer[MAXPATH];
    _getcwd(buffer, MAXPATH);
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "极域卸载工具    Control v2.8.1      适用于:Windows 10 极域电子教室2016" << endl << endl;
    print_warn();
    cout << "程序正在以管理员身份运行!" << endl;
    print_warn();
    cout << "请确保注册表目录与该目录一样，否则3,4,8,9功能可能会无法使用" << endl << "\"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\studentmain.exe\"" << endl;
    print_info();
    cout << "开始释放文件……" << endl;
    if (write_preventkill() && write_msgvbs()) {
        print_info();
        cout << "释放成功" << endl;
    }
    else {
        print_err();
        cout << "释放文件失败，3秒后重试" << endl;
        for (int i = 30; i > 0; i--) {
            print_err();
            cout << "释放文件失败，3秒后重试" << endl;
            print_info();
            cout << "还有" << i / 10.000 << "秒" << endl;
            Sleep(100);
            system("cls");
        }
        system("cls");
        goto begin_first;
    }
    print_info();
    cout << "释放完成！" << endl;
    print_info();
    cout << "开始执行防杀！" << endl;
    system("start \"防杀(请勿关闭)\" ProtectProcess_JY_Uninstall.bat /B");
    print_info();
    cout << "获取当前运行目录中..." << endl;
    print_info();
    cout << "当前运行目录：" << buffer << endl;
    print_info();
    cout << "当前极域注册表位置信息：" << endl;
    print_info();
    system("reg query \"HKLM\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\e-Learning Class V6.0\" /v \"DisplayIcon\"");
    cout << endl << endl;
    goto begin_first;
begin:
    _getcwd(buffer, MAXPATH);
    /*
    BOOL isElevated = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION elevation;
        DWORD dwSize;
        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize)) {
            isElevated = elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }

    if (!isElevated) {
        // 如果不是管理员，以管理员权限重新启动自己
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = TEXT("runas");
        sei.lpFile = buffer;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED)
                ;
        }
        return 0; // 退出原程序
    }
    */
    cout << "极域卸载工具    Control v2.8.1      适用于:Windows 10 极域电子教室2016" << endl << endl;
    print_warn();
    cout << "程序正在以管理员身份运行!" << endl;
    print_warn();
    cout << "请确保注册表目录与该目录一样，否则3,4,8,9功能可能会无法使用" << endl << "\"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\studentmain.exe\"" << endl;
    print_info();
    cout << "获取当前运行目录中..." << endl;
    print_info();
    cout << "当前运行目录：" << buffer << endl;
    print_info();
    cout << "当前极域注册表位置信息：" << endl;
    print_info();
    system("reg query \"HKLM\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\e-Learning Class V6.0\" /v \"DisplayIcon\"");
    cout << endl << endl;
begin_first:
    cout << "-----------功能列表-----------" << endl;
    cout << "1.强杀极域" << endl;
    cout << "2.解除卸载密码" << endl;
    cout << "3.卸载极域(打开卸载)" << endl;
    cout << "4.静默卸载(高级)" << endl;
    cout << "5.封杀极域主程序" << endl;
    cout << "6.恢复极域主程序" << endl;
    cout << "7.恢复极域卸载密码" << endl;
    cout << "8.启动极域" << endl;
    cout << "9.重启极域" << endl;
    cout << "0.重新加载" << endl;
    cout << "i.关于" << endl;
    cout << "r.退出" << endl;
    cout << endl;
    int xx;
    while (1) {
        xx = _getch();
        xx -= 48;
        if (xx == 1) {
            print_info();
            system("taskkill /im studentmain.exe /f /t");
        }
        else if (xx == 2) {
            print_info();
            system("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\TopDomain\\e-learning Class V6.0\" /v SetupType /t REG_SZ /d \"Teacher\" /f");
        }
        else if (xx == 3) {
            system("\"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\unins000.exe\"");
        }
        else if (xx == 4) {
            print_info();
            system("\"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\unins000.exe\" /silent");
            cout << "已开始静默卸载，请坐和放宽，让我们等待一段时间……" << endl;
        }
        else if (xx == 5) {
            print_info();
            system("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\TopDomain\\e-learning Class V6.0\" /v LanguageID /t REG_DWORD /d 1145 /f");
        }
        else if (xx == 6) {
            print_info();
            system("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\TopDomain\\e-learning Class V6.0\" /v LanguageID /t REG_DWORD /d 2052 /f");
        }
        else if (xx == 7) {
            print_info();
            system("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\TopDomain\\e-learning Class V6.0\" /v SetupType /t REG_SZ /d \"Student\" /f");
        }
        else if (xx == 8) {
            system("\"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\Studentmain.exe\"");
        }
        else if (xx == 9) {
            print_info();
            system("taskkill /im studentmain.exe /f /t");
            system("\"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\Studentmain.exe\"");
        }
        else if (xx == 0) {
            system("cls");
            goto begin;
        }
        else if (xx == 57) {
            system("cls");
            setColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << "-----------------关于-----------------" << endl;
            cout << "使用语言：C++" << endl;
            cout << "Windows SDK版本：10.0" << endl;
            cout << "运行环境：需要VC运行库" << endl;
            cout << "开发工具：Visual Studio" << endl << endl;
            cout << "---------------版本信息---------------" << endl;
            cout << "当前版本：2.8.1(控制台版)" << endl;
            cout << "构筑时间：2025年6月1日" << endl;
            cout << "(这不会是最后一版)" << endl << endl;
            cout << "---------------开发人员---------------" << endl;
            cout << "开发者：***(开发者并不是很想透露姓名)" << endl << endl;
            cout << "按任意键回到主程序";
            char temp = _getch();
            setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            system("cls");
            goto begin;
        }
        else if (xx == 66) {
            system("taskkill /im cmd.exe");
            return 0;
        }
        else {
            print_err();
            cout << "你的输入有误。" << endl;
        }
    }
}
