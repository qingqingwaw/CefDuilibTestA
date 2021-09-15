#ifndef CEF_DUILIB_TEST_WEB_CLIENT_H
#define CEF_DUILIB_TEST_WEB_CLIENT_H

#include "include/cef_client.h"
#include "include/base/cef_lock.h"

class CWebClient
    : public CefClient
    , public CefLifeSpanHandler
    , public CefLoadHandler
    , public CefRequestHandler
    , public CefDisplayHandler {
protected:
    CefRefPtr<CefBrowser> m_Browser;
    CefRefPtr<CefDOMDocument> m_Document;
public:
    std::wstring m_url;//加载当前页的url
    HWND m_hWnd; //接收消息的句柄
    CefString m_TitleStr; //网址标题

public:
    CWebClient(void);
    virtual ~CWebClient(void);
    CefRefPtr<CefBrowser> GetBrowser()
    {
        return m_Browser;
    }
    void CloseBrowser(bool force_close);
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
    {
        return this;
    }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE
    {
        return this;
    }
    virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE
    {
        return this;
    }
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE
    {
        return this;
    }
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           int httpStatusCode) OVERRIDE;
    virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             TransitionType transition_type) OVERRIDE;
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString& errorText,
                             const CefString& failedUrl) OVERRIDE;
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                               const CefString& title)OVERRIDE;
    virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
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
                               bool* no_javascript_access) OVERRIDE;
    // 添加CEF的SP虚函数
    IMPLEMENT_REFCOUNTING(CWebClient);
    IMPLEMENT_LOCKING(CWebClient);
};

#endif // CEF_DUILIB_TEST_WEB_CLIENT_H