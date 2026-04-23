/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-3-13)
#ifndef _THEMEDSHADOWWND_H_INCLUDE_
#define _THEMEDSHADOWWND_H_INCLUDE_
#pragma once
#include <map>
#include <math.h>
#include "GdiPlusHelper.h"
using namespace std;
using namespace GdiPlusHelper;

class CThemedShadowWnd : public CWindowImpl<CThemedShadowWnd, CWindow, CControlWinTraits>
{
	// Data members.
private:
	HWND		m_hParentWnd;		// Parent window.
	LONG		m_OriParentProc;	// Original parent window processing.
	int			m_nShadowSize;		// Set the shadow size.
	CRect		m_rcClient;			// Client rect.
	Bitmap*		m_pBitmap;			// GDI+ bitmap for drawing shadow.
	CBitmap		m_bmpShadow;		// GDI bitmap for drawing shadow.
	CPathHelper	m_ShadowPath;		// Round rect path.
	BOOL		m_bResize;			// Indicate window is resized.
	int			m_nBlankArea;		// Set blank area position.

private:
	// Record all the created shadow windows and its parent window.
	static map<HWND, CThemedShadowWnd*>  m_szShadowWindows;

	// Constructor.
public:
	DECLARE_WND_CLASS(_T("WTL_ThemedShadowWindow"))

	CThemedShadowWnd()
	{
		m_hParentWnd	= NULL;
		m_OriParentProc	= 0;
		m_nShadowSize	= 5;
		m_pBitmap		= NULL;
		m_bResize		= FALSE;
		m_nBlankArea	= 1;
	}

	// Operations.
public:
	// Create shadow window.
	HWND Create(const HWND wndParent)
	{
		ATLASSERT( ::IsWindow(wndParent) );
		m_hParentWnd = wndParent;
		CRect rc(1, 1, 1, 1);
		return CWindowImpl<CThemedShadowWnd, CWindow, CControlWinTraits>::Create(0, rc, NULL, WS_VISIBLE, NULL);
	}

	// Set shadow window's parent.
	void SetThemeParent(HWND wndParent)
	{
		ATLASSERT( ::IsWindow(wndParent) );
		m_hParentWnd = wndParent;
	}

	// Adjust shadow window position via parent.
	void AdjustWindowPos()
	{
		CRect rcParent;

		::GetWindowRect(m_hParentWnd, &rcParent);
		rcParent.MoveToY(rcParent.top + m_nShadowSize);
		rcParent.MoveToX(rcParent.left + m_nShadowSize);
		SetWindowPos(m_hParentWnd, rcParent, SWP_NOACTIVATE);

		GetClientRect(m_rcClient);

		// If window was resized, redraw the shadow.
		if (m_bResize == TRUE)
		{
			m_bResize = FALSE;
			DrawShadow();
		}
	}

	// Set the shadow size.
	void SetShadowSize(const int nSize)
	{	
		if (nSize <= 0 || nSize > 255)
		{
			m_nShadowSize = 5;
		}
		else
		{
			m_nShadowSize = nSize;	
		}
	}

	// Set blank area right position.
	void SetRightOffsetArea(const int nRightPos)
	{
		m_nBlankArea = nRightPos;
		if (nRightPos < 0)
		{
			m_nBlankArea = 1;
		}
	}

public:
	// Get parent message.
	static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// Find the shadow window pointer via parent window handle.
		ATLASSERT( m_szShadowWindows.find(hwnd) != m_szShadowWindows.end() );
		CThemedShadowWnd *pThis	= m_szShadowWindows[hwnd];
		WNDPROC pDefProc		= (WNDPROC)pThis->m_OriParentProc;

		switch(uMsg)
		{
		case WM_ERASEBKGND:
		case WM_PAINT:
		case WM_MOVE:
		case WM_ACTIVATE:
		case WM_NCACTIVATE:
			{
				if (::IsWindowVisible(hwnd)) 
				{ 
					pThis->AdjustWindowPos(); 
				}
				break;
			}
		case WM_DESTROY:
			{
				// Destroy the shadow window.
				pThis->DestroyWindow();	
				break;
			}
		case WM_NCDESTROY:
			{
				// Remove shadow window from map.
				m_szShadowWindows.erase(hwnd);	
				break;
			}
		case WM_SHOWWINDOW:
			{
				// the window is being hidden
				if (!wParam)	
				{
					pThis->ShowWindow(SW_HIDE);
				}
				else
				{
					pThis->ShowWindow(SW_SHOW);
				}
				break;
			}
		default:
			{
				break;
			}
		}

		return pDefProc(hwnd, uMsg, wParam, lParam);
	}

	void DrawShadow()
	{
		DeleteOldBrush();

		// Create shadow path.
		Rect rcShadow(m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
		m_ShadowPath.CreateRoundRect(rcShadow, 10);

		m_pBitmap = new Bitmap(rcShadow.Width, rcShadow.Height);
		Graphics graphics(m_pBitmap);

		// Create shadow brush.
		PathGradientBrush brShadow(m_ShadowPath.m_pPath);
		Color clrShadow[3] = {Color::Transparent, Color(255, 0, 0, 0), Color(255, 0, 0, 0)};
		int nCount = 3;

		REAL szPos[3] = {0.0F, 0.05F, 1.0F};
		brShadow.SetInterpolationColors(clrShadow, szPos, nCount);

		// Draw shadow.
		rcShadow.Width	= rcShadow.Width - m_nShadowSize - m_nBlankArea;
		rcShadow.Height	= rcShadow.Height - m_nShadowSize - m_nBlankArea;
		graphics.ExcludeClip(rcShadow);
		graphics.FillPath(&brShadow, m_ShadowPath.m_pPath);

		// Update layered window.
		m_pBitmap->GetHBITMAP((ARGB)Color::Black, &m_bmpShadow.m_hBitmap);

		CClientDC dc(m_hWnd);

		CDC dcCompat;
		dcCompat.CreateCompatibleDC();
		dcCompat.SelectBitmap(m_bmpShadow);

		BITMAP bmpInfo = {0};
		m_bmpShadow.GetBitmap(&bmpInfo);
		CSize size(bmpInfo.bmWidth, bmpInfo.bmHeight);
		CRect rcWindow;
		GetWindowRect(&rcWindow);

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 128, AC_SRC_ALPHA };

		CPoint ptWnd(rcWindow.left, rcWindow.top);
		CPoint ptSource(0, 0);

		UpdateLayeredWindow(m_hWnd, dc.m_hDC, &ptWnd, &size,
			dcCompat.m_hDC, &ptSource, 0, &bf, ULW_ALPHA);
	}

private:
	// Delete old brush.
	void DeleteOldBrush()
	{
		if (m_pBitmap)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
	}

	// Message map and handlers.
public:
	BEGIN_MSG_MAP(CThemedShadowWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// Record shadow window and its parent window.
		m_szShadowWindows.insert( make_pair(m_hParentWnd, this) );

		// Reset window styles.
		ModifyStyle(WS_MAXIMIZEBOX | WS_SIZEBOX | WS_CAPTION | WS_DLGFRAME, 0, 0);

		// The window style should be WS_EX_LAYERED.
		SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		ModifyStyleEx(WS_EX_TOPMOST, WS_EX_NOACTIVATE);

		// Set parent window original processing.
		m_OriParentProc = ::GetWindowLong(m_hParentWnd, GWL_WNDPROC);
		::SetWindowLong(m_hParentWnd, GWL_WNDPROC, (LONG)ParentProc);

		LPCREATESTRUCT lpcs = ( LPCREATESTRUCT ) lParam;
		LRESULT res = DefWindowProc( uMsg, wParam, ( LPARAM ) lpcs );
		return res;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_bResize = TRUE;
		bHandled = FALSE;
		return 0;
	}
};

#endif // _THEMEDSHADOWWND_H_INCLUDE_