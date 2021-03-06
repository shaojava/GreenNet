// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMinimize();
	void OnFeedback();
	void OnSetting();

	void OnSwitchPorn();
	void OnSwitchTrush();
	void OnSwitchFish();

	void OnSearchPorn();
	void OnSearchTrush();
	void OnSearchFish();

	void OnSearch();
	void OnCheckNew();

	//托盘通知消息处理函数
	LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
	//演示如何响应菜单事件
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnMouseMove(UINT nFlags, CPoint point);

protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_fankui", OnFeedback)
		EVENT_NAME_COMMAND(L"btn_set", OnSetting)
		EVENT_NAME_COMMAND(L"switch_porn", OnSwitchPorn)
		EVENT_NAME_COMMAND(L"switch_trush", OnSwitchTrush)
		EVENT_NAME_COMMAND(L"switch_fish", OnSwitchFish)
		EVENT_NAME_COMMAND(L"chakan_porn", OnSearchPorn)
		EVENT_NAME_COMMAND(L"chakan_trush", OnSearchTrush)
		EVENT_NAME_COMMAND(L"chakan_fish", OnSearchFish)
		EVENT_NAME_COMMAND(L"search", OnSearch)
		EVENT_NAME_COMMAND(L"checknew", OnCheckNew)
		EVENT_MAP_END()
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_CLOSE(OnClose)

		//托盘消息处理
		MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
		MSG_WM_COMMAND(OnCommand)

		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:

	BOOL            m_bMouseMove1;
	BOOL            m_bMouseMove2;
	BOOL            m_bMouseMove3;
	BOOL			m_bLayoutInited;
	SShellNotifyIcon shellNotifyIcon;
};
