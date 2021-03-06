// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"

#include <dwmapi.h>
#include "extend_ui/SSwitch.h"
#include "DetailInfoDlg.h"
#include "BlacklistDlg.h"
#pragma comment(lib,"dwmapi.lib")

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
	m_bMouseMove1 = FALSE;
	m_bMouseMove2 = FALSE;
	m_bMouseMove3 = FALSE;
}

CMainDlg::~CMainDlg()
{
	shellNotifyIcon.Hide();
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	shellNotifyIcon.Create(m_hWnd,GETRESPROVIDER->LoadIcon(_T("ICON_LOGO"),16));
	shellNotifyIcon.Show();
	return 0;
}

void CMainDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	SetMsgHandled(FALSE);
	SImageWnd *pImg = (SImageWnd *)FindChildByName(L"skin_descripte");
	ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_descripte_01");
	if (NULL == pImg || NULL == pSkin)
		return;

	SWindow *pPornWnd = FindChildByName(L"img_porn");
	SWindow *pTrushWnd = FindChildByName(L"img_trush");
	SWindow *pFishWnd = FindChildByName(L"img_fish");	

	if ((pPornWnd != NULL && !pPornWnd->GetWindowRect().PtInRect(point))
		&& (pTrushWnd != NULL && !pTrushWnd->GetWindowRect().PtInRect(point))
		&& (pFishWnd != NULL && !pFishWnd->GetWindowRect().PtInRect(point)))
	{

		if (m_bMouseMove1 || m_bMouseMove2 || m_bMouseMove3)
			pImg->SetSkin(pSkin);	

		m_bMouseMove1 = FALSE;
		m_bMouseMove2 = FALSE;
		m_bMouseMove3 = FALSE;
		return;
	}

	if (!m_bMouseMove1 && pPornWnd->GetWindowRect().PtInRect(point))
	{
		m_bMouseMove1 = TRUE;
		ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_descripte_02");
		pImg->SetSkin(pSkin);		
	}
	
	if (!m_bMouseMove2 && pTrushWnd->GetWindowRect().PtInRect(point))
	{
		m_bMouseMove2 = TRUE;
		ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_descripte_03");
		pImg->SetSkin(pSkin);
	}
	
	if (!m_bMouseMove3 && pFishWnd->GetWindowRect().PtInRect(point))
	{
		m_bMouseMove3 = TRUE;
		ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_descripte_04");
		pImg->SetSkin(pSkin);
	}

}

//TODO:消息映射
void CMainDlg::OnClose()
{
	PostMessage(WM_QUIT);
}

void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnFeedback()
{
	ShellExecute(NULL, L"open", L"http://www.baidu.com", NULL, NULL, SW_SHOW);
}

void CMainDlg::OnSetting()
{
	MessageBox(0, L"设置", L"设置", 0);
}

#include <helper/smenu.h>
LRESULT CMainDlg::OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/)
{
	switch (lParam)
	{
	case  WM_RBUTTONDOWN:
	{
            //显示右键菜单
            SMenu menu;
            menu.LoadMenu(_T("menu_tray"),_T("smenu"));
            POINT pt;
            GetCursorPos(&pt);
            menu.TrackPopupMenu(0,pt.x,pt.y,m_hWnd);
	}break;
	case WM_LBUTTONDOWN:
	{
		//显示/隐藏主界面
		if (IsIconic())
		   ShowWindow(SW_SHOWNORMAL);
		else
		   ShowWindow(SW_MINIMIZE);
	}break;
	default:
		break;
	}
	return S_OK;
}

//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}

void CMainDlg::OnSwitchPorn()
{
	SSwitch *pSwith = (SSwitch *)FindChildByName(L"switch_porn");	
	SImageWnd *pImgWnd = (SImageWnd *)FindChildByName(L"img_porn");

	if (pSwith == NULL || pImgWnd == NULL)
		return;
	ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_net_porn");
	if (pSwith->IsOpen())
	{				
		pImgWnd->SetSkin(pSkin, 0);
	}
	else
	{
		pImgWnd->SetSkin(pSkin, 2);
	}
	pImgWnd->Invalidate();		
}

void CMainDlg::OnSwitchTrush()
{
	SSwitch *pSwith = (SSwitch *)FindChildByName(L"switch_trush");	
	SImageWnd *pImgWnd = (SImageWnd *)FindChildByName(L"img_trush");

	if (pSwith == NULL || pImgWnd == NULL)
		return;
	ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_net_trush");
	if (pSwith->IsOpen())
	{				
		pImgWnd->SetSkin(pSkin, 0);
	}
	else
	{
		pImgWnd->SetSkin(pSkin, 2);
	}
	pImgWnd->Invalidate();		
}

void CMainDlg::OnSwitchFish()
{
	SSwitch *pSwith = (SSwitch *)FindChildByName(L"switch_fish");	
	SImageWnd *pImgWnd = (SImageWnd *)FindChildByName(L"img_fish");

	if (pSwith == NULL || pImgWnd == NULL)
		return;
	ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(L"skin_net_fish");
	if (pSwith->IsOpen())
	{				
		pImgWnd->SetSkin(pSkin, 0);
	}
	else
	{
		pImgWnd->SetSkin(pSkin, 2);
	}
	pImgWnd->Invalidate();		
}

void CMainDlg::OnSearchPorn()
{
	CDetailInfoDlg *pDlg = new CDetailInfoDlg(L"共拦截色情网站(178)个");
	pDlg->Create(NULL);
	pDlg->SendMessage(WM_INITDIALOG);
	pDlg->CenterWindow(pDlg->m_hWnd);
	pDlg->ShowWindow(SW_SHOWNORMAL);
}

void CMainDlg::OnSearchTrush()
{
	CDetailInfoDlg *pDlg = new CDetailInfoDlg(L"共拦截垃圾网站(178)个");
	pDlg->Create(NULL);
	pDlg->SendMessage(WM_INITDIALOG);
	pDlg->CenterWindow(pDlg->m_hWnd);
	pDlg->ShowWindow(SW_SHOWNORMAL);
}

void CMainDlg::OnSearchFish()
{
	CDetailInfoDlg *pDlg = new CDetailInfoDlg(L"共拦截钓鱼网站(178)个");
	pDlg->Create(NULL);
	pDlg->SendMessage(WM_INITDIALOG);
	pDlg->CenterWindow(pDlg->m_hWnd);
	pDlg->ShowWindow(SW_SHOWNORMAL);
}

void CMainDlg::OnSearch()
{
	CBlacklistDlg *pDlg = new CBlacklistDlg(L"黑名单(17)");
	pDlg->Create(NULL);
	pDlg->SendMessage(WM_INITDIALOG);
	pDlg->CenterWindow(pDlg->m_hWnd);
	pDlg->ShowWindow(SW_SHOWNORMAL);
}

void CMainDlg::OnCheckNew()
{
	MessageBox(0, L"检查更新", L"检查更新", 0);
}





