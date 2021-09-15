// DuiLibTest01.cpp : 定义应用程序的入口点。
//

#include "framework.h"

#include "TestWindowWnd.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (AllocConsole()) {
        ::SetConsoleTitle(_T("DebugWindow"));
        FILE* out = nullptr;
        freopen_s(&out, "CONOUT$", "w", stdout);
    }

    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("res"));

    TestWindowWnd* pFrame = new TestWindowWnd();
    pFrame->Create(NULL, _T("TestWindow"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW);

    pFrame->CenterWindow();
    pFrame->ShowWindow(true);

    CPaintManagerUI::MessageLoop();

    delete pFrame;

    return 0;
}

