#include <Windows.h>
#include <CommCtrl.h>
#include <string>

#pragma comment(lib, "Comctl32.lib") // 链接库

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{

    // 初始化公共控件库
    INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icex);

    int nButton = 0;
    TASKDIALOGCONFIG tdc = { 0 };
    tdc.cbSize = sizeof(tdc);
    tdc.hwndParent = NULL;
    tdc.dwFlags = TDF_USE_COMMAND_LINKS;
    tdc.pszWindowTitle = L"你好，这个世界";
    tdc.pszMainInstruction = L"Hello, World!";
    tdc.pszContent = L"你有两个选项：";
    TASKDIALOG_BUTTON buttons[] = {
        { IDYES, L"好(&Y)" },
        { IDNO,  L"不好(&N)" }
    };
    tdc.pButtons = buttons;
    tdc.cButtons = ARRAYSIZE(buttons);
    tdc.nDefaultButton = IDYES;
    tdc.pszMainIcon = TD_INFORMATION_ICON;

    TaskDialogIndirect(&tdc, &nButton, NULL, NULL);

    if (nButton == IDYES)
    {
        TaskDialog(NULL, NULL, L"问候1", L"哈哈哈哈哈，欢迎来到这个美丽的世界，Human", NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
    }
    else if (nButton == IDNO)
    {
        TaskDialog(NULL, NULL, L"问候2", L"不是，我草泥马的，我是不是给你脸给多了，我草泥马的", NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);

        char videoPath[MAX_PATH];
        GetModuleFileNameA(NULL, videoPath, MAX_PATH);
        std::string exeDir(videoPath);
        exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
        std::string fullVideoPath = exeDir + "\\main.mp4";

        // 检查文件是否存在
        DWORD fileAttributes = GetFileAttributesA(fullVideoPath.c_str());
        if (fileAttributes == INVALID_FILE_ATTRIBUTES)
        {
            // 文件不存在，显示自定义消息
            TaskDialog(NULL, NULL, L"文件错误", L"找不到视频文件 main.mp4，你运气真好", 
                      NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
            return 0;
        }

        std::string cmd = "cmd /c start \"\" \"" + fullVideoPath + "\"";
        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        BOOL success = CreateProcessA(
            NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

        if (success) {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        if (!success) {
            TaskDialog(NULL, NULL, L"呃啊", L"我暂时放过你", NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
        }
    }

    return 0;
}