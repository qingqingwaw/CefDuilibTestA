// CEFDuiLibTest.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Resource.h"

#include "CWebClient.h"
#include "CefDuilibTest.h"
#include "include/cef_app.h"
//#include "include/internal/cef_win.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

    HRESULT Hr = ::CoInitialize(NULL);
    if (FAILED(Hr)) return 0;

    CefRefPtr<CefApp> spApp;
    //CefMainArgs main_args;
    CefMainArgs main_args(hInstance); // +++

    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    CefSettings cSettings;
    CefSettingsTraits::init(&cSettings);
    cSettings.no_sandbox = true; // +++
    cSettings.multi_threaded_message_loop = true;
    CefInitialize(main_args, cSettings, spApp, nullptr);

    CCefDuiLibTest* pFrame = new CCefDuiLibTest();
    if (pFrame == NULL) return 0;  //
    pFrame->Create(NULL, _T("这是一个最简单的测试用exe，修改test_01.xml就可以看到效果"), WS_MINIMIZEBOX | WS_POPUP | WS_VISIBLE, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowWindow(true);

    if (!cSettings.multi_threaded_message_loop) {
        //Run the CEF message loop. This function will block until the application
        //recieves a WM_QUIT message.
        CefRunMessageLoop();
    }
    else {
        CPaintManagerUI::MessageLoop();
    }
    CefShutdown();
    ::CoUninitialize();
    return 0;
}
