#pragma once
#include "UIlib.h"

using namespace DuiLib;
class CefViewWnd : public WindowImplBase {
public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM, bool& bHandled) override;
    virtual void Notify(TNotifyUI& msg) override;
    virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                        BOOL& bHandled) override;
    virtual void InitWindow() override;
    virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
    virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

protected:
    virtual CDuiString GetSkinFolder() override
    { 
        return _T("res");
    };

    virtual CDuiString GetSkinFile() override
    {
        return _T("cef_view.xml");
    }
    virtual LPCTSTR GetWindowClassName(void) const override
    {
        return _T("CefViewWndClass");
    };

private:
};

class TestWindowWnd : public WindowImplBase {
public:
    virtual void Notify(TNotifyUI& msg) override;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                        BOOL& bHandled) override;
    virtual void InitWindow() override;
    virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
    virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

protected:
    virtual CDuiString GetSkinFolder() override;
    virtual CDuiString GetSkinFile() override;
    virtual LPCTSTR GetWindowClassName(void) const override;

private:
    CefViewWnd view1;
    CefViewWnd view2;
};
