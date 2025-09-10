#include <Windows.h>
#include <CommCtrl.h>
#include <string>

#pragma comment(lib, "Comctl32.lib") // ���ӿ�

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{

    // ��ʼ�������ؼ���
    INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icex);

    int nButton = 0;
    TASKDIALOGCONFIG tdc = { 0 };
    tdc.cbSize = sizeof(tdc);
    tdc.hwndParent = NULL;
    tdc.dwFlags = TDF_USE_COMMAND_LINKS;
    tdc.pszWindowTitle = L"��ã��������";
    tdc.pszMainInstruction = L"Hello, World!";
    tdc.pszContent = L"��������ѡ�";
    TASKDIALOG_BUTTON buttons[] = {
        { IDYES, L"��(&Y)" },
        { IDNO,  L"����(&N)" }
    };
    tdc.pButtons = buttons;
    tdc.cButtons = ARRAYSIZE(buttons);
    tdc.nDefaultButton = IDYES;
    tdc.pszMainIcon = TD_INFORMATION_ICON;

    TaskDialogIndirect(&tdc, &nButton, NULL, NULL);

    if (nButton == IDYES)
    {
        TaskDialog(NULL, NULL, L"�ʺ�1", L"��������������ӭ����������������磬Human", NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
    }
    else if (nButton == IDNO)
    {
        TaskDialog(NULL, NULL, L"�ʺ�2", L"���ǣ��Ҳ�����ģ����ǲ��Ǹ����������ˣ��Ҳ������", NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);

        char videoPath[MAX_PATH];
        GetModuleFileNameA(NULL, videoPath, MAX_PATH);
        std::string exeDir(videoPath);
        exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
        std::string fullVideoPath = exeDir + "\\main.mp4";

        // ����ļ��Ƿ����
        DWORD fileAttributes = GetFileAttributesA(fullVideoPath.c_str());
        if (fileAttributes == INVALID_FILE_ATTRIBUTES)
        {
            // �ļ������ڣ���ʾ�Զ�����Ϣ
            TaskDialog(NULL, NULL, L"�ļ�����", L"�Ҳ�����Ƶ�ļ� main.mp4�����������", 
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
            TaskDialog(NULL, NULL, L"����", L"����ʱ�Ź���", NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
        }
    }

    return 0;
}