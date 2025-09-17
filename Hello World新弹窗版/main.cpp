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
    // 初始化公共控件库
    INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icex);

    // 初始化随机数生成器
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int Button = 0;
    TASKDIALOGCONFIG tdc = { 0 };
    tdc.cbSize = sizeof(tdc);
    tdc.hwndParent = NULL;
    tdc.dwFlags = TDF_USE_COMMAND_LINKS;
    tdc.pszWindowTitle = L"Hello World！";
    tdc.pszMainInstruction = L"你好，这个世界。赛博朋克之风正劲，我们一起跨越时间的壁垒，探索未知的未来。";
    tdc.pszContent = L"请选择你的命运：";
    
    TASKDIALOG_BUTTON buttons[] = {
        { IDYES, L"接受命运(&Y)\n成为赛博英雄" },
        { IDNO,  L"拒绝命运(&N)\n继续当个普通人" },
        { IDCANCEL, L"我要考虑一下(&T)\n让我深思熟虑" }
    };
    tdc.pButtons = buttons;
    tdc.cButtons = ARRAYSIZE(buttons);
    tdc.nDefaultButton = IDYES;
    tdc.pszMainIcon = TD_INFORMATION_ICON;

    TaskDialogIndirect(&tdc, &Button, NULL, NULL);

    if (Button == IDYES)
    {
        const wchar_t* messages[] = {
            L"Wake up, Samurai. We have a city to burn.", // 经典开场白
            L"植入义体：斯安威斯坦... 完成", // 义体安装
            L"检测到网络接入点：夜之城数据流异常", // 网络异常提示
            L"你的传奇正在被书写，来生酒吧见..." // 结局暗示
        };

        for (const auto& msg : messages)
        {
            TaskDialog(NULL, NULL, L"系统提示", msg, NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
            Sleep(1000); // 增加戏剧性效果
        }
    }
    else if (Button == IDNO)
    {
        // 随机选择一个"生气"的回应
        const wchar_t* angryResponses[] = {
            L"哼！你会后悔的！",
            L"这可能是你最错误的决定！",
            L"不给面子是吧？我是不是给你脸给多了？",
            L"你以为这样就结束了吗？"
        };
        int randomIndex = std::rand() % 4;
        
        TaskDialog(NULL, NULL, L"警告", angryResponses[randomIndex], NULL, TDCBF_OK_BUTTON, TD_WARNING_ICON, NULL);

        // 原有的视频播放逻辑
        char videoPath[MAX_PATH];
        GetModuleFileNameA(NULL, videoPath, MAX_PATH);
        std::string exeDir(videoPath);
        exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
        std::string fullVideoPath = exeDir + "\\main.mp4";

        DWORD fileAttributes = GetFileAttributesA(fullVideoPath.c_str());
        if (fileAttributes == INVALID_FILE_ATTRIBUTES)
        {
            // 文件不存在时显示随机的讽刺消息
            const wchar_t* mockingMessages[] = {
                L"算了算了，看你这么可怜...",
                L"今天心情好，就饶了你吧",
                L"你走运了，视频文件不见了",
                L"逃过一劫，下次可就没这么好运了"
            };
            randomIndex = std::rand() % 4;
            
            TaskDialog(NULL, NULL, L"文件错误，呃啊", mockingMessages[randomIndex], 
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
            L"思考是好事...",
            L"但机会稍纵即逝...",
            L"下次见面时，希望你能做出选择..."
        };

        for (const auto& msg : Message)
        {
            TaskDialog(NULL, NULL, L"深思熟虑", msg, NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
            Sleep(800);
        }
    }

    return 0;
}