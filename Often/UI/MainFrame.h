#pragma once
#include "DuiHelper.h"
#include "CPUUsage/CPUUsage.h"
#include "CMemoryUsage.h"
#include "UI/CCircleProgressUI.h"
#include "OpenHardwareMonitorApi/OpenHardwareMonitorApi.h"
#include <atomic>

class CMainFrame : public WindowImplBase
{
public:
    CMainFrame();
    ~CMainFrame();
    
private:
    CDuiString GetSkinFile() override;
    LPCTSTR GetWindowClassName() const override;
    UINT GetClassStyle() const override;
    void Notify(TNotifyUI& msg) override;
    void OnSelectChange(TNotifyUI& msg);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    CControlUI* CreateControl(LPCTSTR pstrClass) override;
private:

    // 初始化UI
    void InitWindow() override;
    void InitControlManager();


private:

    // 硬件信息
    void MonitorThreadCallback();
    void InitOpenHardwareMonitor();
    void OnRefreshHardwareInfo();
    void OnTimerQueryHardwareInfo();


private:
    // Control
    CLabelUI* m_lbl_memory_usage;
    CLabelUI* m_lbl_cpu_freq;
    CLabelUI* m_lbl_cpu_temperature;
    CLabelUI* m_lbl_gpu_usage;
    CLabelUI* m_lbl_gpu_temperature;
    CLabelUI* m_lbl_hdd_temperature;
    CLabelUI* m_lbl_Mainboard_temperature;
    CCircleProgressUI* m_circle_cpu_usage;

    CTabLayoutUI* m_pTabSwitch;
    //
    CCPUUsage m_CpuUsage;
    CMemoryUsage m_MemoryUsage;
    std::shared_ptr<OpenHardwareMonitorApi::IOpenHardwareMonitor> m_pMonitor{};

    int m_iCpuUsage;
    int m_iMemoryUsage;
    float m_fCpuFreq;
    float m_fCpuTemperature;

    float m_fGpuUsage;
    float m_fGpuTemperature;

    float m_fHDDTemperature;
    float m_fMainboardTemperature;


};

