#pragma once
#include "DuiHelper.h"
#include <Gdiplus.h>
class CCircleProgressUI : public CProgressUI
{
    DECLARE_DUICONTROL(CCircleProgressUI)
public:
    CCircleProgressUI();
    

    LPCTSTR GetClass() const;
    

    void PaintBkColor(HDC hDC);

    void PaintForeColor(HDC hDC);
    
    void PaintForeImage(HDC hDC);

    void SetCenterColor(DWORD dwCenterColor);
protected:
    DWORD m_dwCenterColor;
};
