#pragma once
#include "DuiHelper.h"
#include "CPUUsage/CPUUsage.h"

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
private:
    void MonitorThreadCallback();
private:
    // Control
    CLabelUI* m_lbl_cpu_usage;

    //
    CCPUUsage m_CpuUsage;
};

