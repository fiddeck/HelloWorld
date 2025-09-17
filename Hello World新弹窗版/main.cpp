#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <random>
#include <ctime>

#pragma comment(lib, "Comctl32.lib")

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // ��ʼ�������ؼ���
    INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icex);

    // ��ʼ�������������
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int Button = 0;
    TASKDIALOGCONFIG tdc = { 0 };
    tdc.cbSize = sizeof(tdc);
    tdc.hwndParent = NULL;
    tdc.dwFlags = TDF_USE_COMMAND_LINKS;
    tdc.pszWindowTitle = L"Hello World��";
    tdc.pszMainInstruction = L"��ã�������硣�������֮������������һ���Խʱ��ı��ݣ�̽��δ֪��δ����";
    tdc.pszContent = L"��ѡ��������ˣ�";
    
    TASKDIALOG_BUTTON buttons[] = {
        { IDYES, L"��������(&Y)\n��Ϊ����Ӣ��" },
        { IDNO,  L"�ܾ�����(&N)\n����������ͨ��" },
        { IDCANCEL, L"��Ҫ����һ��(&T)\n������˼����" }
    };
    tdc.pButtons = buttons;
    tdc.cButtons = ARRAYSIZE(buttons);
    tdc.nDefaultButton = IDYES;
    tdc.pszMainIcon = TD_INFORMATION_ICON;

    TaskDialogIndirect(&tdc, &Button, NULL, NULL);

    if (Button == IDYES)
    {
        const wchar_t* messages[] = {
            L"Wake up, Samurai. We have a city to burn.", // ���俪����
            L"ֲ�����壺˹����˹̹... ���", // ���尲װ
            L"��⵽�������㣺ҹ֮���������쳣", // �����쳣��ʾ
            L"��Ĵ������ڱ���д�������ưɼ�..." // ��ְ�ʾ
        };

        for (const auto& msg : messages)
        {
            TaskDialog(NULL, NULL, L"ϵͳ��ʾ", msg, NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
            Sleep(1000); // ����Ϸ����Ч��
        }
    }
    else if (Button == IDNO)
    {
        // ���ѡ��һ��"����"�Ļ�Ӧ
        const wchar_t* angryResponses[] = {
            L"�ߣ�����ڵģ�",
            L"��������������ľ�����",
            L"���������ǰɣ����ǲ��Ǹ����������ˣ�",
            L"����Ϊ�����ͽ�������"
        };
        int randomIndex = std::rand() % 4;
        
        TaskDialog(NULL, NULL, L"����", angryResponses[randomIndex], NULL, TDCBF_OK_BUTTON, TD_WARNING_ICON, NULL);

        // ԭ�е���Ƶ�����߼�
        char videoPath[MAX_PATH];
        GetModuleFileNameA(NULL, videoPath, MAX_PATH);
        std::string exeDir(videoPath);
        exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
        std::string fullVideoPath = exeDir + "\\main.mp4";

        DWORD fileAttributes = GetFileAttributesA(fullVideoPath.c_str());
        if (fileAttributes == INVALID_FILE_ATTRIBUTES)
        {
            // �ļ�������ʱ��ʾ����ķ����Ϣ
            const wchar_t* mockingMessages[] = {
                L"�������ˣ�������ô����...",
                L"��������ã����������",
                L"�������ˣ���Ƶ�ļ�������",
                L"�ӹ�һ�٣��´οɾ�û��ô������"
            };
            randomIndex = std::rand() % 4;
            
            TaskDialog(NULL, NULL, L"�ļ���������", mockingMessages[randomIndex], 
                      NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
            return 0;
        }

        std::string cmd = "cmd /c start \"\" \"" + fullVideoPath + "\"";
        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else if (Button == IDCANCEL)
    {
        const wchar_t* Message[] = {
            L"˼���Ǻ���...",
            L"���������ݼ���...",
            L"�´μ���ʱ��ϣ����������ѡ��..."
        };

        for (const auto& msg : Message)
        {
            TaskDialog(NULL, NULL, L"��˼����", msg, NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
            Sleep(800);
        }
    }

    return 0;
}