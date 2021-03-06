// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"


#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
	m_pUninstallPro = NULL;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	m_pUninstallPro = FindChildByName2<SProgressEx>(L"prog_test");
	return 0;
}


void CMainDlg::OnClose()
{
	PostMessage(WM_QUIT);
}

void CMainDlg::OnBtnTiyan()
{
	MessageBox(0, L"立即体验", L"立即体验", 0);
}

void CMainDlg::OnUninstall()
{
	STabCtrl *pTabCtrl = FindChildByName2<STabCtrl>(L"tab_main");
	if (pTabCtrl) 
	{
		pTabCtrl->SetCurSel(L"uninstall");
		CSimpleWnd::SetTimer(PERCENT_TIMER, 500);
	}
}

void CMainDlg::OnTimer(UINT_PTR idEvent)
{
	static int nPercent = 0;

	if (idEvent == PERCENT_TIMER)
	{	
		nPercent += 10;		
		m_pUninstallPro->SetValue(nPercent);
		if (nPercent == 100)
		{
			::KillTimer(m_hWnd, PERCENT_TIMER);
			STabCtrl *pTabCtrl = FindChildByName2<STabCtrl>(L"tab_main");
			if (pTabCtrl) 
			{
				pTabCtrl->SetCurSel(L"uninstall_over");	
			}
		}
	}
	SetMsgHandled(FALSE);
}