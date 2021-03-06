// MainDlg.cpp : implementation of the CBlacklistDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BlacklistDlg.h"
#include "helper/SAdapterBase.h"

#include <dwmapi.h>
#include "extend_ui/STextButton.h"
#pragma comment(lib,"dwmapi.lib")


class CBlacklistAdapterFix : public SAdapterBase
{
public:
	CBlacklistAdapterFix()
	{
		m_nSel = -1;
	}
	virtual int getCount()
	{
		return 17;
	}   

	virtual void getView(int position, SWindow * pItem,pugi::xml_node xmlTemplate)
	{
		if(pItem->GetChildrenCount()==0)
		{
			pItem->InitFromXml(xmlTemplate);
		}

		STextButton *pText1 = (STextButton *)pItem->FindChildByName(L"blacklist_test1");

		pItem->SetUserData(position);
		pItem->GetEventSet()->subscribeEvent(EVT_CMD, Subscriber(&CBlacklistAdapterFix::OnButtonClick,this));

		pText1->SetUserData(position);
		pText1->GetEventSet()->subscribeEvent(EVT_CMD,Subscriber(&CBlacklistAdapterFix::OnButtonClick2,this));

		if (position == m_nSel)
		{
			if (pText1 != NULL)
				pText1->SetWindowText(L"取消");
		}
		else
		{
			if (pText1 != NULL)
				pText1->SetWindowText(L"");
		}			
	}

	bool OnButtonClick(EventArgs *pEvt)
	{		
		SWindow *pItem = sobj_cast<SWindow>(pEvt->sender);
		if (pItem == NULL)
			return false;

		m_nSel = pItem->GetUserData();
		notifyDataSetChanged();		

		return true;
	}


	bool OnButtonClick2(EventArgs *pEvt)
	{		
		MessageBox(0, L"取消", 0, 0);

		return true;
	}


private:
	int m_nSel;
};


CBlacklistDlg::CBlacklistDlg(LPCTSTR chContent) : SHostWnd(_T("LAYOUT:XML_BLACKLISTWND"))
{
	m_chContent = (LPTSTR)chContent;
	m_bLayoutInited = FALSE;
}

CBlacklistDlg::~CBlacklistDlg()
{
	
}

int CBlacklistDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}
 
BOOL CBlacklistDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	SStatic *pWnd = (SStatic *)FindChildByName(L"text_content");
	if (pWnd != NULL)
	{
		pWnd->SetWindowText(m_chContent);
	}

	//行高可变的列表
	SListView *pLstViewFlex = FindChildByName2<SListView>("lv_test_fix");
	if(pLstViewFlex)
	{
		IAdapter *pAdapter = new CBlacklistAdapterFix;
		pLstViewFlex->SetAdapter(pAdapter);
		pAdapter->Release();
	}

	return 0;
}

//TODO:消息映射
void CBlacklistDlg::OnClose()
{
	:: DestroyWindow(m_hWnd);
}

void CBlacklistDlg::OnBtnAdd()
{
	MessageBox(0, L"添加", L"添加", 0);
}



