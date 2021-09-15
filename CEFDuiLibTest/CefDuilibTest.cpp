// App.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "CefDuilibTest.h"

//#include "include/cef_app.h"
//#include "include/internal/cef_win.h"

#define OFFSETX 95 //Xƫ��ֵ
#define OFFSETY 110 //����ʱYƫ��ֵ
#define OFFSETY_1 20 //����ʱYƫ��ֵ

CCefDuiLibTest::CCefDuiLibTest()
    : m_pTabLayoutUI(NULL)
    , m_pTabSwitchHor(NULL)
    , m_BackBtn(NULL)
    , m_ForwardBtn(NULL)
    , m_indexSwitch(0)
{

}
CCefDuiLibTest::~CCefDuiLibTest()
{
    m_cWebClient.clear();
    m_UEdit.clear();
}
//��ҳ��ת
void CCefDuiLibTest::GoNewUrl()
{
    // ��ȡ�������ַ
    CDuiString strUrl;
    CEditUI* pEdit = (CEditUI*)m_pm.FindControl(_T("url"));
    if (pEdit) {
        strUrl = pEdit->GetText();

        // �����ַΪ���򷵻�
        if (strUrl.Compare(_T("")) == 0)
            return;
    }

    // ��ȡ��ǰ��ʾ��tab
    int index = m_pTabLayoutUI->GetCurSel();
    CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
    if (pHor) {
        const CefString url(strUrl.GetData());
        m_cWebClient.at(index)->GetBrowser()->GetMainFrame()->LoadURL(url);
        m_UEdit.at(index) = url.c_str();
        // ���ı�ǩ����
        int iCount = m_pTabSwitchHor->GetCount();
        for (int i = 0; i < iCount; i++) {
            COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
            CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
            if (pHaveHor == pHor) {
                pOpt->SetToolTip(m_cWebClient.at(index)->m_TitleStr.c_str());
                return;
            }
        }
        MaxMinCefWindow(OFFSETX, OFFSETY);
    }
}
//ˢ�µ�ǰҳ��
void CCefDuiLibTest::RefreshUrl()
{
    int index = m_pTabLayoutUI->GetCurSel();
    m_cWebClient.at(index)->GetBrowser()->Reload();
}
//����ҳǩ
void CCefDuiLibTest::NewPage(std::wstring Url)
{
    CDuiString teststr;
    teststr = Url.c_str();
    m_UEdit.push_back(teststr);

    CefRefPtr<CWebClient>client(new CWebClient());
    m_cWebClient.push_back(client);
    client->m_hWnd = m_hWnd;
    CefWindowInfo info;
    RECT rect;
    GetClientRect(this->GetHWND(), &rect);
    RECT rectnew = rect;
    rectnew.top = rect.top + OFFSETX;
    rectnew.bottom = rect.bottom - OFFSETY_1;
    rectnew.left = rect.left;
    rectnew.right = rect.right;
    info.SetAsChild(m_hWnd, rectnew);
    CefBrowserSettings browserSettings;
    CefBrowserHost::CreateBrowser(info, static_cast<CefRefPtr<CefClient>>(client), Url.c_str(), browserSettings, nullptr, nullptr);
    for (UINT i = 0; i < m_cWebClient.size(); i++) {
        if (m_cWebClient.at(i)->GetBrowser() && !m_cWebClient.at(i)->GetBrowser()->GetMainFrame()->GetURL().empty()) {
            CefRefPtr<CefBrowserHost> t_host = m_cWebClient.at(i)->GetBrowser()->GetHost();
            CefWindowHandle hwnd = t_host->GetWindowHandle();
            if (i < m_cWebClient.size() - 1) {
                MoveWindow(hwnd, 0, 0, 0, 0, false);
            }
            else {
                int width = rectnew.right - rectnew.left;
                int height = rectnew.bottom - rectnew.top;
                MoveWindow(hwnd, rectnew.left, rectnew.top, width, height, true);
            }
        }
    }
    CEditUI* pEdit = (CEditUI*)m_pm.FindControl(_T("url"));
    if (pEdit) {
        pEdit->SetText(Url.c_str());
    }
}
//�������ڴ�С
void CCefDuiLibTest::MaxMinCefWindow(int offsetx, int offsety)
{
    RECT rect;
    GetClientRect(this->GetHWND(), &rect);
    RECT rectnew = rect;
    rectnew.top = rect.top + offsetx; //95
    rectnew.bottom = rect.bottom - offsety; //110
    rectnew.left = rect.left;
    rectnew.right = rect.right;
    int t_index = m_pTabLayoutUI->GetCurSel();
    for (UINT i = 0; i < m_cWebClient.size(); i++) {
        CefWindowHandle hwnd = m_cWebClient.at(i)->GetBrowser()->GetHost()->GetWindowHandle();
        if (i != t_index) {
            MoveWindow(hwnd, 0, 0, 0, 0, false);
        }
        else {
            int width = rectnew.right - rectnew.left;
            int height = rectnew.bottom - rectnew.top;
            MoveWindow(hwnd, rectnew.left, rectnew.top, width, height, true);
        }
    }
}
//����ı�
void CCefDuiLibTest::TitleChage(const CefString& str)
{

    int index = m_pTabLayoutUI->GetCurSel();
    CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
    if (pHor) {
        int iCount = m_pTabSwitchHor->GetCount();
        for (int i = 0; i < iCount; i++) {
            COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
            CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
            if (pHaveHor == pHor) {
                if (str.length() > 8) {
                    wchar_t strtilte[100] = {NULL};
                    wcsncpy(strtilte, str.c_str(), 6);
                    wcsncat(strtilte, _T("..."), 3);
                    pOpt->SetText(strtilte);
                }
                else {
                    pOpt->SetText(str.c_str());
                }
                pOpt->SetToolTip(str.c_str());
                break;
            }
        }
    }
}
//ɾ��ҳǩ
void CCefDuiLibTest::TableDel()
{
    int t_Index = 0;
    vector<CefRefPtr<CWebClient>>::iterator cWebClientit = m_cWebClient.begin();
    if (m_UEdit.size() > 1) {
        int t_moveIndex = m_indexSwitch;
        if (m_indexSwitch > 0)t_moveIndex = m_indexSwitch - 1;
        COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(m_indexSwitch);
        CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
        m_pTabSwitchHor->Remove(pOpt);
        m_pTabLayoutUI->Remove(pHaveHor);

        COptionUI* p = (COptionUI*)m_pTabSwitchHor->GetItemAt(t_moveIndex);
        p->Selected(true);

        CHorizontalLayoutUI* pHaveHor1 = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(t_moveIndex);
        m_pTabLayoutUI->SelectItem(pHaveHor1);
        for (vector<CDuiString>::iterator it = m_UEdit.begin(); it != m_UEdit.end();)   //forѭ���в�Ҫit++
        {
            if (t_Index == m_indexSwitch) {
                ::MoveWindow(m_cWebClient.at(m_indexSwitch)->GetBrowser()->GetHost()->GetWindowHandle(), 0, 0, 0, 0, true);
                m_cWebClient.at(m_indexSwitch)->CloseBrowser(true);
                m_cWebClient.erase(cWebClientit++);
                m_UEdit.erase(it++);
                MaxMinCefWindow(OFFSETX, OFFSETY);
                ::CoUninitialize();
                break;
            }
            else {
                it++;
                cWebClientit++;
            }
            t_Index++;
        }
    }
    else {
        m_UEdit.at(0) = _T("www.hao123.com");
        m_cWebClient.at(0)->GetBrowser()->GetMainFrame()->LoadURL(m_UEdit.at(0).GetData());
        CEditUI* pEdit = (CEditUI*)m_pm.FindControl(_T("url"));
        if (pEdit) {
            pEdit->SetText(m_UEdit.at(0));
        }
    }
}
//����
void CCefDuiLibTest::SearchGo()
{
    CDuiString sText = m_pSearchEdit->GetText();
    if (!sText.IsEmpty()) {
        CDuiString sUrl;
        sUrl.Format(_T("https://www.baidu.com/s?ie=utf-8&wd=%s"), sText.GetData());
        std::wstring T_urL = sUrl.GetData();
        // ������ǩOPTION��ť
        /*CDuiString sAttr;
        COptionUI* pOpt = new COptionUI;
        sAttr.Format(_T("name=\"IE_\" width=\"100\" height=\"30\" normalimage=\"tabbar_normal.png\" hotimage=\"tabbar_hover.png\" \
                        pushedimage=\"tabbar_pushed.png\" selectedimage=\"tabbar_pushed.png\" group=\"demo_list_header\""));
        pOpt->ApplyAttributeList(sAttr);

        int iCount = m_pTabSwitchHor->GetCount();
        m_pTabSwitchHor->AddAt(pOpt, iCount-1);

        // ������ǩ����
        CHorizontalLayoutUI* pHor = new CHorizontalLayoutUI;

        // �Ѳ�����ӽ���ǩ
        m_pTabLayoutUI->Add(pHor);
        m_pTabLayoutUI->SetTag((UINT_PTR)pHor);

        m_pTabLayoutUI->SelectItem(pHor);//ѡ�б�ǩ��ť����

        // �ѱ�ǩ��ť�Ͳ��ֹ�������
        pOpt->SetTag((UINT_PTR)pHor);

        ::PostMessageA(this->m_hWnd, WM_DUI_TABTAG, NULL, NULL);

        NewPage(T_urL);*/
        NewTable(T_urL);
    }
}
//����
void CCefDuiLibTest::NewTable(std::wstring url)
{
    CDuiString sAttr;
    COptionUI* pOpt = new COptionUI;
    sAttr.Format(_T("name=\"IE_\" width=\"100\" height=\"30\" normalimage=\"tabbar_normal.png\" hotimage=\"tabbar_hover.png\" \
					pushedimage=\"tabbar_pushed.png\" selectedimage=\"tabbar_pushed.png\" group=\"demo_list_header\""));
    pOpt->ApplyAttributeList(sAttr);
    int iCount = m_pTabSwitchHor->GetCount();
    m_pTabSwitchHor->AddAt(pOpt, iCount - 1);

    // ������ǩ����
    CHorizontalLayoutUI* pHor = new CHorizontalLayoutUI;

    // �Ѳ�����ӽ���ǩ
    m_pTabLayoutUI->Add(pHor);
    m_pTabLayoutUI->SetTag((UINT_PTR)pHor);

    m_pTabLayoutUI->SelectItem(pHor);//ѡ�б�ǩ��ť����

    // �ѱ�ǩ��ť�Ͳ��ֹ�������
    pOpt->SetTag((UINT_PTR)pHor);


    ::PostMessageA(this->m_hWnd, WM_DUI_TABTAG, NULL, NULL);

    NewPage(url);
    pOpt->SetText(url.c_str());
}
//����¼�
void CCefDuiLibTest::OnClick(TNotifyUI& msg)
{
    // �رհ�ť	
    if (msg.pSender->GetName().Find(_T("closebtn")) != -1) {
        Close();
    }
    // ��С����ť
    else if (msg.pSender->GetName().Find(_T("minbtn")) != -1) {
        SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return;
    }
    // ��󻯰�ť
    else if (msg.pSender->GetName().Find(_T("maxbtn")) != -1) {
        CButtonUI* pBtn = (CButtonUI*)m_pm.FindControl(_T("restorebtn"));
        pBtn->SetVisible(true);
        msg.pSender->SetVisible(false);
        SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
        MaxMinCefWindow(OFFSETX, OFFSETY);
        return;
    }
    // ��ԭ��ť
    else if (msg.pSender->GetName().Find(_T("restorebtn")) != -1) {
        CButtonUI* pBtn = (CButtonUI*)m_pm.FindControl(_T("maxbtn"));
        pBtn->SetVisible(true);
        msg.pSender->SetVisible(false);
        SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
        MaxMinCefWindow(OFFSETX, OFFSETY);
        return;
    }
    // ���IE��ǩ��option
    else if (msg.pSender->GetName().Find(_T("IE_")) != -1) {
        COptionUI* pOpt = (COptionUI*)msg.pSender;

        CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)pOpt->GetTag();
        if (pHor) {
            RECT rc = pOpt->GetPos();
            if (msg.ptMouse.x > rc.right - 20 && msg.ptMouse.y < rc.top + 15) {
                int iCount = m_pTabSwitchHor->GetCount();
                for (int i = 0; i < iCount; i++) {
                    COptionUI* pOpt1 = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
                    if (pOpt == pOpt1) {
                        m_indexSwitch = i;
                        ::PostMessageA(this->m_hWnd, WM_DUI_SELTABTAG, NULL, NULL);
                        return;
                    }
                }
            }
            m_pTabLayoutUI->SelectItem(pHor);
            RECT rect;
            GetClientRect(this->GetHWND(), &rect);
            RECT rectnew = rect;
            rectnew.top = rect.top + OFFSETX;
            rectnew.bottom = rect.bottom - OFFSETY_1;
            rectnew.left = rect.left;
            rectnew.right = rect.right;
            int t_index = m_pTabLayoutUI->GetCurSel();
            for (UINT i = 0; i < m_cWebClient.size(); i++) {
                CefWindowHandle hwnd = m_cWebClient.at(i)->GetBrowser()->GetHost()->GetWindowHandle();
                if (i != t_index)
                    MoveWindow(hwnd, 0, 0, 0, 0, false);
                else {
                    CEditUI* pEdit = (CEditUI*)m_pm.FindControl(_T("url"));
                    if (pEdit) {
                        pEdit->SetText(m_UEdit.at(t_index));
                    }
                    int width = rectnew.right - rectnew.left;
                    int height = rectnew.bottom - rectnew.top;
                    MoveWindow(hwnd, rectnew.left, rectnew.top, width, height, true);
                }
            }
        }
    }
    // ���������ť
    else if (msg.pSender->GetName().Find(_T("Nav")) != -1) {
        GoNewUrl();
    }
    // ��ӱ�ǩ
    else if (msg.pSender->GetName().Find(_T("Add")) != -1) {

        // ������ǩOPTION��ť
        /*CDuiString sAttr;
        COptionUI* pOpt = new COptionUI;
        sAttr.Format(_T("name=\"IE_\" width=\"100\" height=\"30\" normalimage=\"tabbar_normal.png\" hotimage=\"tabbar_hover.png\" \
                         pushedimage=\"tabbar_pushed.png\" selectedimage=\"tabbar_pushed.png\" group=\"demo_list_header\""));
        pOpt->ApplyAttributeList(sAttr);
        int iCount = m_pTabSwitchHor->GetCount();
        m_pTabSwitchHor->AddAt(pOpt, iCount-1);

        // ������ǩ����
        CHorizontalLayoutUI* pHor = new CHorizontalLayoutUI;

        // �Ѳ�����ӽ���ǩ
        m_pTabLayoutUI->Add(pHor);
        m_pTabLayoutUI->SetTag((UINT_PTR)pHor);

        m_pTabLayoutUI->SelectItem(pHor);//ѡ�б�ǩ��ť����

        // �ѱ�ǩ��ť�Ͳ��ֹ�������
        pOpt->SetTag((UINT_PTR)pHor);


        ::PostMessageA(this->m_hWnd, WM_DUI_TABTAG, NULL, NULL);

        NewPage(_T("www.hao123.com"));
        pOpt->SetText(_T("http://www.hao123.com"));*/
        NewTable(_T("www.hao123.com"));
    }
    else if (msg.pSender->GetName().Find(_T("refreshbtnr")) != -1) {
        RefreshUrl();
    }
    else if (msg.pSender->GetName().Find(_T("Forward")) != -1) {
        int index = m_pTabLayoutUI->GetCurSel();
        CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
        if (pHor) {
            int iCount = m_pTabSwitchHor->GetCount();
            for (int i = 0; i < iCount; i++) {
                COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
                CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
                if (pHaveHor == pHor) {
                    CefRefPtr<CefBrowser> t_browser = m_cWebClient.at(index)->GetBrowser();
                    if (t_browser->CanGoForward()) {
                        t_browser->GoForward();
                    }
                    break;
                }
            }
        }
    }
    else if (msg.pSender->GetName().Find(_T("Back")) != -1) {
        int index = m_pTabLayoutUI->GetCurSel();
        CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
        if (pHor) {
            int iCount = m_pTabSwitchHor->GetCount();
            for (int i = 0; i < iCount; i++) {
                COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
                CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
                if (pHaveHor == pHor) {
                    CefRefPtr<CefBrowser> t_browser = m_cWebClient.at(index)->GetBrowser();
                    if (t_browser->CanGoBack()) {
                        t_browser->GoBack();
                    }
                    break;
                }
            }
        }
    }
    else if (msg.pSender->GetName().Find(_T("search_gosearch_go")) != -1) {
        SearchGo();
    }
    else if (msg.pSender->GetName().Find(_T("Main_Type")) != -1) {
        NewTable(_T("www.hao123.com"));
    }
}

//��Ϣ��Ӧ
void CCefDuiLibTest::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnInitWnd();
    }
    else if (msg.sType == _T("click")) {
        OnClick(msg);
    }
    else if (msg.sType == _T("return")) {
        GoNewUrl();
    }
}
//ϵͳ��Ϣ
LRESULT CCefDuiLibTest::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    LRESULT lRes = 0;

    if (uMsg == WM_TITLECHANGE) {
        CefString str = *(CefString*)lParam;
        TitleChage(str);
    }
    if (uMsg == WM_LOADSTART) {
        int index = m_pTabLayoutUI->GetCurSel();
        CLabelUI* pLable = (CLabelUI*)m_pm.FindControl((_T("statusbar")));
        pLable->SetTextColor(0xff0000);

        std::wstring  str = _T("���ڼ���");
        str = str + m_cWebClient.at(index)->m_url.c_str();
        pLable->SetText(str.c_str());


        CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
        if (pHor) {
            int iCount = m_pTabSwitchHor->GetCount();
            for (int i = 0; i < iCount; i++) {
                COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
                CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
                if (pHaveHor == pHor) {
                    m_UEdit.at(index) = m_cWebClient.at(index)->m_url.c_str();
                    break;
                }
            }
        }
    }
    else if (uMsg == WM_LOADEND) {
        CLabelUI* pLable = (CLabelUI*)m_pm.FindControl((_T("statusbar")));
        pLable->SetTextColor(0xff0000);
        int index = m_pTabLayoutUI->GetCurSel();
        CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
        if (pHor) {
            int iCount = m_pTabSwitchHor->GetCount();
            for (int i = 0; i < iCount; i++) {
                COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
                CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
                if (pHaveHor == pHor) {
                    if (m_cWebClient.at(index)->GetBrowser()->CanGoBack()) {
                        m_BackBtn->SetEnabled(true);
                    }
                    else {
                        m_BackBtn->SetEnabled(false);
                    }
                    if (m_cWebClient.at(index)->GetBrowser()->CanGoForward()) {
                        m_ForwardBtn->SetEnabled(true);
                    }
                    else {
                        m_ForwardBtn->SetEnabled(false);
                    }
                    m_UEdit.at(index) = m_cWebClient.at(index)->m_url.c_str();
                    break;
                }
            }
        }
        CEditUI* pEdit = (CEditUI*)m_pm.FindControl(_T("url"));
        if (pEdit) {
            pEdit->SetText(m_UEdit.at(index));
        }
        pLable->SetText(_T("�������"));
    }

    else if (uMsg == WM_LOADPOPUP) {
        std::wstring T_urL = *(std::wstring*)lParam;
        // ������ǩOPTION��ť
        CDuiString sAttr;
        COptionUI* pOpt = new COptionUI;
        sAttr.Format(_T("name=\"IE_\" width=\"100\" height=\"30\" normalimage=\"tabbar_normal.png\" hotimage=\"tabbar_hover.png\" \
			pushedimage=\"tabbar_pushed.png\" selectedimage=\"tabbar_pushed.png\" group=\"demo_list_header\""));
        pOpt->ApplyAttributeList(sAttr);

        int iCount = m_pTabSwitchHor->GetCount();
        m_pTabSwitchHor->AddAt(pOpt, iCount - 1);

        // ������ǩ����
        CHorizontalLayoutUI* pHor = new CHorizontalLayoutUI;

        // �Ѳ�����ӽ���ǩ
        m_pTabLayoutUI->Add(pHor);
        m_pTabLayoutUI->SetTag((UINT_PTR)pHor);

        m_pTabLayoutUI->SelectItem(pHor);//ѡ�б�ǩ��ť����

        // �ѱ�ǩ��ť�Ͳ��ֹ�������
        pOpt->SetTag((UINT_PTR)pHor);

        ::PostMessageA(this->m_hWnd, WM_DUI_TABTAG, NULL, NULL);

        NewPage(T_urL);
    }
    else if (uMsg == WM_DUI_TABTAG) {
        int iCount = m_pTabSwitchHor->GetCount();
        COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(iCount - 2);
        if (pOpt) {
            pOpt->Selected(true);
        }
    }
    else if (uMsg == WM_DUI_SELTABTAG) {

        TableDel();
    }

    return __super::MessageHandler(uMsg, wParam, lParam, bHandled);
}
//��ȡƤ��·��
DuiLib::CDuiString CCefDuiLibTest::GetSkinFolder()
{
    return _T("skin\\");
}
//��ȡƤ������
DuiLib::CDuiString CCefDuiLibTest::GetSkinFile()
{
    return _T("test_01.xml");
}

//��ȡ����
LPCTSTR CCefDuiLibTest::GetWindowClassName(void) const
{

    return _T("LoginWinClass");
}
//�����ؼ�
CControlUI* CCefDuiLibTest::CreateControl(LPCTSTR pstrClass)
{
    //if (_tcscmp(pstrClass,_T("ButtonGif")) == 0) return new CButtonGifUI;
    return NULL;
}

void CCefDuiLibTest::OnFinalMessage(HWND hWnd)
{
    __super::OnFinalMessage(hWnd);
    delete this;
}

LRESULT CCefDuiLibTest::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    ::PostQuitMessage(0L);
    return 0;
}
void CCefDuiLibTest::OnInitWnd()
{
    //��ǩ����
    m_pTabLayoutUI = (CTabLayoutUI*)m_pm.FindControl(_T("switch"));

    // ��ǩ��ť����
    m_pTabSwitchHor = (CHorizontalLayoutUI*)(m_pm.FindControl(_T("tabswitch")));

    //ǰ����ť
    m_ForwardBtn = (CButtonUI*)m_pm.FindControl(_T("Forward"));
    //���˰�ť
    m_BackBtn = (CButtonUI*)m_pm.FindControl(_T("Back"));
    //����
    m_pSearchEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("search_edit")));

    m_BackBtn->SetEnabled(false);
    m_ForwardBtn->SetEnabled(false);

    CefRefPtr<CWebClient> client(new CWebClient());
    m_cWebClient.push_back(client);
    m_cWebClient.at(0)->m_hWnd = m_hWnd;
    CefWindowInfo info;
    RECT rect;
    GetClientRect(this->GetHWND(), &rect);
    RECT rectnew = rect;
    rectnew.top = rect.top + OFFSETX;
    rectnew.bottom = rect.bottom - OFFSETY_1;
    rectnew.left = rect.left;
    rectnew.right = rect.right;
    info.SetAsChild(m_hWnd, rectnew);
    CefBrowserSettings browserSettings;
    CefString url = _T("http://www.baidu.com");
    CefBrowserHost::CreateBrowser(info, static_cast<CefRefPtr<CefClient>>(m_cWebClient.at(0)), url, browserSettings, nullptr, nullptr);
    CDuiString str(_T("http://www.baidu.com"));
    m_UEdit.push_back(str);

    // ����ҳ�ؼ��ͱ�ǩ���ֹ�������
    CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)(m_pm.FindControl(_T("HorBrowser")));
    /*if (pHor)
    {
        CWebBrowserUI* pWer = (CWebBrowserUI*)(m_PaintManager.FindControl(_T("Browser")));
        if (pWer)
        {
            pHor->SetTag((UINT_PTR)pWer);
        }
    }*/

    // �ѵ�һ��option��ť�ͱ�ǩ���ֹ�������
    COptionUI* pOpt = (COptionUI*)(m_pm.FindControl(_T("IE_1")));
    if (pOpt) {
        pOpt->SetTag((UINT_PTR)pHor);
    }
}



