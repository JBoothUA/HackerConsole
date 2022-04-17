#include "stdafx.h"
#include "resource.h"

#include "DlgSettingsStyles.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

DlgSettingsStyles::DlgSettingsStyles(CComPtr<IXMLDOMElement>& pOptionsRoot)
: DlgSettingsBase(pOptionsRoot)
{
	IDD = IDD_SETTINGS_STYLES;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsStyles::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_stylesSettings.Load(m_pOptionsRoot);

	CUpDownCtrl	spin;
	UDACCEL udAccel;

	spin.Attach(GetDlgItem(IDC_SPIN_INSIDE_BORDER));
	spin.SetRange(0, 10);
	spin.Detach();

	spin.Attach(GetDlgItem(IDC_SPIN_SPLIT_BAR_SIZE));
	spin.SetRange(0, 8);
	spin.Detach();

	spin.Attach(GetDlgItem(IDC_SPIN_QUAKE_ANIMATION_TIME));
	spin.SetRange(10, 20000);
	udAccel.nSec = 0;
	udAccel.nInc = 10;
	spin.SetAccel(1, &udAccel);
	spin.Detach();

	EnableQuakeControls();

	DoDataExchange(DDX_LOAD);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsStyles::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CWindow		staticCtl(reinterpret_cast<HWND>(lParam));
	CDCHandle	dc(reinterpret_cast<HDC>(wParam));

	if (staticCtl.m_hWnd == GetDlgItem(IDC_SELECTION_COLOR))
	{
		CBrush	brush(::CreateSolidBrush(m_stylesSettings.crSelectionColor));
		CRect	rect;

		staticCtl.GetClientRect(&rect);
		dc.FillRect(&rect, brush);
		return 0;
	}
	else if (staticCtl.m_hWnd == GetDlgItem(IDC_HIGHLIGHT_COLOR))
	{
		CBrush	brush(::CreateSolidBrush(m_stylesSettings.crHighlightColor));
		CRect	rect;

		staticCtl.GetClientRect(&rect);
		dc.FillRect(&rect, brush);
		return 0;
	}

	bHandled = FALSE;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsStyles::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (wID == IDOK)
	{
		DoDataExchange(DDX_SAVE);

		if (m_stylesSettings.dwInsideBorder > 10) m_stylesSettings.dwInsideBorder = 10;
		if (m_stylesSettings.dwSplitBarSize > 8) m_stylesSettings.dwSplitBarSize = 8;

		StylesSettings& stylesSettings = g_settingsHandler->GetAppearanceSettings().stylesSettings;

		stylesSettings = m_stylesSettings;

		m_stylesSettings.Save(m_pOptionsRoot);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsStyles::OnClickedQuake(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);
	EnableQuakeControls();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsStyles::OnClickedSelColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/)
{
	CColorDialog	dlg(m_stylesSettings.crSelectionColor, CC_FULLOPEN);

	if (dlg.DoModal() == IDOK)
	{
		// update color
		m_stylesSettings.crSelectionColor = dlg.GetColor();
		CWindow(hWndCtl).Invalidate();
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsStyles::OnClickedHiColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/)
{
	CColorDialog	dlg(m_stylesSettings.crHighlightColor, CC_FULLOPEN);

	if (dlg.DoModal() == IDOK)
	{
		// update color
		m_stylesSettings.crHighlightColor = dlg.GetColor();
		CWindow(hWndCtl).Invalidate();
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void DlgSettingsStyles::EnableQuakeControls()
{
	GetDlgItem(IDC_STATIC_QUAKE_1).EnableWindow(m_stylesSettings.bQuake);
	GetDlgItem(IDC_STATIC_QUAKE_2).EnableWindow(m_stylesSettings.bQuake);
	GetDlgItem(IDC_QUAKE_ANIMATION_TIME).EnableWindow(m_stylesSettings.bQuake);
	GetDlgItem(IDC_SPIN_QUAKE_ANIMATION_TIME).EnableWindow(m_stylesSettings.bQuake);
}

//////////////////////////////////////////////////////////////////////////////
