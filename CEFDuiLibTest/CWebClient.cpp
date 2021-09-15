#include "framework.h"
#include"CWebClient.h"
#include "include/cef_app.h"

CWebClient::CWebClient()
{
    m_hWnd = NULL;
}
CWebClient::~CWebClient()
{

}
void CWebClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    m_Browser = browser;
}
void CWebClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CefQuitMessageLoop();
}

void CWebClient::OnLoadStart(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             TransitionType transition_type)
{

    m_url = browser->GetMainFrame()->GetURL();
    ::PostMessage(m_hWnd, WM_LOADSTART, NULL, (LPARAM)&m_url);
    return __super::OnLoadStart(browser, frame, transition_type);
}

void CWebClient::OnLoadEnd(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           int httpStatusCode)
{
    m_url = browser->GetMainFrame()->GetURL();
    ::PostMessage(m_hWnd, WM_LOADEND, NULL, (LPARAM)&m_url);
}

void CWebClient::OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString& errorText,
                             const CefString& failedUrl)
{

}
void CWebClient::OnTitleChange(CefRefPtr<CefBrowser> browser,
                               const CefString& title)
{
    m_TitleStr = title;
    ::PostMessage(m_hWnd, WM_TITLECHANGE, NULL, (LPARAM)&m_TitleStr);
}
bool CWebClient::OnBeforePopup(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               const CefString& target_url,
                               const CefString& target_frame_name,
                               CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                               bool user_gesture,
                               const CefPopupFeatures& popupFeatures,
                               CefWindowInfo& windowInfo,
                               CefRefPtr<CefClient>& client,
                               CefBrowserSettings& settings,
                               CefRefPtr<CefDictionaryValue>& extra_info,
                               bool* no_javascript_access)
{
    m_url = target_url;
    ::PostMessage(m_hWnd, WM_LOADPOPUP, NULL, (LPARAM)&m_url);
    return true;
}
void CWebClient::CloseBrowser(bool force_close)
{

}
