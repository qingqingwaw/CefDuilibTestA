#include "TestWindowWnd.h"


LRESULT CefViewWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM, bool& bHandled)
{
    bHandled = FALSE;

    return 0;
}

void CefViewWnd::Notify(TNotifyUI& msg)
{

}

LRESULT CefViewWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                        BOOL& bHandled)
{
    bHandled = FALSE;

    switch (uMsg) {
        case WM_CLOSE:
            printf("CefViewWnd receive message: WM_CLOSE = %u\n", uMsg); break;
        case WM_DESTROY:
            printf("CefViewWnd receive message: WM_DESTROY = %u\n", uMsg); break;
        case WM_NCDESTROY:
            printf("CefViewWnd receive message: WM_NCDESTROY = %u\n", uMsg); break;
        case WM_QUIT:
            printf("CefViewWnd receive message: WM_QUIT = %u\n", uMsg); break;
        case SC_CLOSE:
            printf("CefViewWnd receive message: SC_CLOSE = %u\n", uMsg); break;
        default:
            break;
    }

    return 0;
}

void CefViewWnd::InitWindow()
{
    printf("CefViewWnd::InitWindow\n");
}
LRESULT CefViewWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    printf("CefViewWnd::OnClose\n");
    return 0;
}

LRESULT CefViewWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    printf("CefViewWnd::OnDestroy. hWnd: %#0x\n", (int)m_hWnd);
    return 0;
}

CDuiString TestWindowWnd::GetSkinFolder()
{
    return _T("res");
}

CDuiString TestWindowWnd::GetSkinFile()
{
    return _T("skin.xml");
}
LPCTSTR TestWindowWnd::GetWindowClassName(void) const
{
    return _T("TestWindowClass");
}

void TestWindowWnd::Notify(TNotifyUI& msg)
{
    if (_tcsicmp(msg.sType, _T("click")) == 0) {
        if (_tcsicmp(msg.pSender->GetName(), _T("btn_close")) == 0) {
            printf("TestWindowWnd::Notify click msg, msg sender is btn_close\n");
            Close(0);
        }
    }
}

LRESULT TestWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CLOSE:
            printf("receive message: WM_CLOSE = %u\n", uMsg); break;
        case WM_DESTROY:
            printf("receive message: WM_DESTROY = %u\n", uMsg); break;
        case WM_NCDESTROY:
            printf("receive message: WM_NCDESTROY = %u\n", uMsg); break;
        case WM_QUIT:
            printf("receive message: WM_QUIT = %u\n", uMsg); break;
        case SC_CLOSE:
            printf("receive message: SC_CLOSE = %u\n", uMsg); break;
        default:
            break;
    }
    return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT TestWindowWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam,
                                           LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;

    return 0;
}


void TestWindowWnd::InitWindow()
{
    printf("TestWindowWnd::InitWindow start\n");
    RECT rc;
    ::GetWindowRect(GetHWND(), &rc);

    view1.Create(GetHWND(), nullptr, UI_WNDSTYLE_CHILD, 0, rc);
    //view1.CenterWindow();
    view1.ShowWindow(true);

    //view2.Create(GetHWND(), nullptr, UI_WNDSTYLE_CHILD & ~WS_CHILD | WS_POPUP, 0, rc);
    view2.Create(GetHWND(), nullptr, UI_WNDSTYLE_CHILD | WS_POPUP, 0, rc);
    view2.ShowWindow(true);
    printf("TestWindowWnd::InitWindow end\n");
}

LRESULT TestWindowWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = TRUE;

    printf("TestWindowWnd::OnClose\n");
    //::DestroyWindow(m_hWnd); // 不能直接这样destroy 父窗口,否则主进程无法退出。
    //PostMessage(WM_DESTROY, 0, 0);
    //::PostMessage(NULL, WM_DESTROY, 0, 0); // 无效消息，窗口无法收到 WM_DESTROY 消息
    ::PostQuitMessage(0);

    return 0;
}

LRESULT TestWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    printf("TestWindowWnd::OnDestroy. hWnd: %#0x\n", (int)m_hWnd);
    return 0;
}


