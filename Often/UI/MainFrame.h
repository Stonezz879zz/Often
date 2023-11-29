#pragma once
#include "DuiHelper.h"
#include "CPUUsage/CPUUsage.h"
#include "CMemoryUsage.h"
#include "UI/ControlEx.h"

class CMainFrame : public WindowImplBase
{
public:
    CMainFrame();
    ~CMainFrame();
    
private:
    CDuiString GetSkinFile() override;
    LPCTSTR GetWindowClassName() const override;
    UINT GetClassStyle() const override;
    void InitWindow() override;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    CControlUI* CreateControl(LPCTSTR pstrClass) override;
private:
    void MonitorThreadCallback();
private:
    // Control
    CLabelUI* m_lbl_cpu_usage;
    CCircleProgressUI* m_circle_cpu_usage;
    //
    CCPUUsage m_CpuUsage;
    CMemoryUsage m_MemoryUsage;
    int m_iCpuUsage;
    int m_iMemoryUsage;
};

