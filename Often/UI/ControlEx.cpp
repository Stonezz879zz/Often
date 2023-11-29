//#include "StdAfx.h"
#include "ControlEx.h"


IMPLEMENT_DUICONTROL(CCircleProgressUI)

void CCircleProgressUI::PaintForeImage(HDC hDC)
{
}

void CCircleProgressUI::SetCenterColor(DWORD dwCenterColor)
{
    m_dwCenterColor = dwCenterColor;
}

CCircleProgressUI::CCircleProgressUI():
    m_dwCenterColor(0xFFFFFFFF)
{
}

LPCTSTR CCircleProgressUI::GetClass() const
{
    return _T("CircleProgress");
}

void CCircleProgressUI::PaintBkColor(HDC hDC)
{
}

void CCircleProgressUI::PaintForeColor(HDC hDC)
{

    Gdiplus::Graphics g(hDC);
    g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);//¿¹¾â³Ý

    RECT rcPos = GetPos();
    Gdiplus::Rect rcfPos(rcPos.left, rcPos.top, rcPos.right - rcPos.left, rcPos.bottom - rcPos.top);

    Gdiplus::SolidBrush bkbrush(m_dwBackColor);

    g.FillPie(&bkbrush, rcfPos, 0, 360);

    Gdiplus::SolidBrush forebrush(m_dwForeColor);
    int nStartDegree = 90;
    int nSweepDegree = (int)(360.0f * (m_nValue * 1.0f / (m_nMax - m_nMin)));
    g.FillPie(&forebrush, rcfPos, nStartDegree, nSweepDegree);

    Gdiplus::SolidBrush coverbrush(m_dwCenterColor);
    CDuiRect rcCenter = rcPos;
    rcCenter.left += 10;
    rcCenter.top += 10;
    rcCenter.right -= 10;
    rcCenter.bottom -= 10;
    Gdiplus::Rect rcf1Pos(rcCenter.left, rcCenter.top, rcCenter.right - rcCenter.left, rcCenter.bottom - rcCenter.top);

    g.FillPie(&coverbrush, rcf1Pos, 0, 360);

    g.ReleaseHDC(hDC);
}
