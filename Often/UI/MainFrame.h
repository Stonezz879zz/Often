#pragma once
#include "DuiHelper.h"
#include "CPUUsage/CPUUsage.h"
#include "CMemoryUsage.h"
#include "UI/CCircleProgressUI.h"
#include "OpenHardwareMonitorApi/OpenHardwareMonitorApi.h"

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
    CLabelUI* m_lbl_memory_usage;
    CLabelUI* m_lbl_cpu_freq;
    CLabelUI* m_lbl_cpu_temperature;
    CLabelUI* m_lbl_gpu_usage;
    CLabelUI* m_lbl_gpu_temperature;
    CLabelUI* m_lbl_hdd_temperature;
    CLabelUI* m_lbl_Mainboard_temperature;
    CCircleProgressUI* m_circle_cpu_usage;
    //
    CCPUUsage m_CpuUsage;
    CMemoryUsage m_MemoryUsage;
    std::shared_ptr<OpenHardwareMonitorApi::IOpenHardwareMonitor> m_pMonitor{};

    CRITICAL_SECTION m_minitor_lib_critical;        //用于访问OpenHardwareMonitor进行线程同步的临界区对象
    int m_iCpuUsage;
    int m_iMemoryUsage;
    float m_fCpuFreq;
    float m_fCpuTemperature;

    float m_fGpuUsage;
    float m_fGpuTemperature;

    float m_fHDDTemperature;
    float m_fMainboardTemperature;


};

