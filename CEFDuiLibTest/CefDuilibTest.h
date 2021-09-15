
#include "UIlib.h"

#ifdef GetNextSibling
#undef GetNextSibling
#undef GetFirstChild
#endif

#include "CWebClient.h"
#include "include/cef_app.h"
//#include <atlstr.h>
#include <vector>

using namespace std;
using namespace DuiLib;

#define  WM_CREATE_NEW  WM_USER+302
#define  WM_DUI_TABTAG	WM_USER+400
#define  WM_DUI_SELTABTAG WM_USER+401

class CCefDuiLibTest: public WindowImplBase
{
public:
	CCefDuiLibTest();
	virtual ~CCefDuiLibTest();
private:
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/);
	virtual void Notify(TNotifyUI& msg);
	virtual void OnFinalMessage( HWND hWnd );
	virtual void OnClick(TNotifyUI& msg);
private:
	void  GoNewUrl(); //ת���µ�ַ
	void  MaxMinCefWindow(int offsetx,int offsety); //�����С�����Ŵ��ڴ�С 
	void  NewPage(std::wstring Url);//����ҳǩ 
	void  RefreshUrl();//ˢ�µ�ǰҳ��
	void  TitleChage(const CefString &str); //����ı� 
	void  TableDel();//ɾ��ҳǩ 
	void  OnInitWnd();
	void  SearchGo();//���� 
	void  NewTable(std::wstring url);

private:
	CTabLayoutUI*			m_pTabLayoutUI;		//��ǩ����
	CHorizontalLayoutUI*	m_pTabSwitchHor;	//��ǩ��ť����
	CButtonUI*				m_BackBtn;			//ǰ����ť
	CButtonUI*				m_ForwardBtn;		//���˰�ť
	int						m_indexSwitch;		//��ǩ����
	vector<CefRefPtr<CWebClient>>   m_cWebClient; 
	vector<CDuiString>      m_UEdit;	//��ǩҳ��ַ
	CEditUI* m_pSearchEdit;
};