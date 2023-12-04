#include "MainFrame.h"
#include "MessageDefine.h"
#include "Common/Common.h"
#include <thread>

float m_fGpuUsage;
float m_fGpuTemperature;

float m_fHDDTemperature;
float m_fMainboardTemperature;
CMainFrame::CMainFrame()
    :m_circle_cpu_usage(nullptr),
    m_lbl_cpu_freq(nullptr),
    m_lbl_cpu_temperature(nullptr),
    m_lbl_gpu_usage(nullptr),
    m_lbl_gpu_temperature(nullptr),
    m_lbl_memory_usage(nullptr),
    m_lbl_hdd_temperature(nullptr),
    m_lbl_Mainboard_temperature(nullptr),
    m_pTabSwitch(nullptr),
    m_iCpuUsage(0),
    m_fCpuFreq(0.0),
    m_fCpuTemperature(0.0),
    m_fGpuUsage(0.0),
    m_fGpuTemperature(0.0),
    m_iMemoryUsage(0),
    m_fHDDTemperature(0.0),
    m_fMainboardTemperature(0.0)
{
}

CMainFrame::~CMainFrame()
{
}

CDuiString CMainFrame::GetSkinFile()
{
    return _T("main.xml");
}

LPCTSTR CMainFrame::GetWindowClassName() const
{
    return _T("MainWnd");
}

UINT CMainFrame::GetClassStyle() const
{
    return CS_DBLCLKS;
}

void CMainFrame::InitWindow()
{
    InitOpenHardwareMonitor();
    InitControlManager();
    

    
}

void CMainFrame::InitControlManager()
{
    m_pTabSwitch = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("tab_switch")));
    if (!m_pTabSwitch) return;

    m_circle_cpu_usage = static_cast<CCircleProgressUI*>(m_pm.FindControl(_T("circle_cpu_usage")));
    if (!m_circle_cpu_usage) return;

    m_circle_cpu_usage->SetCenterColor(m_circle_cpu_usage->GetBkColor());

    m_lbl_cpu_freq = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_cpu_freq")));
    if (!m_lbl_cpu_freq) return;

    m_lbl_cpu_temperature = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_cpu_temperature")));
    if (!m_lbl_cpu_temperature) return;

    m_lbl_gpu_usage = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_gpu_usage")));
    if (!m_lbl_gpu_usage) return;

    m_lbl_gpu_temperature = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_gpu_temperature")));
    if (!m_lbl_gpu_temperature) return;

    m_lbl_memory_usage = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_memory_usage")));
    if (!m_lbl_memory_usage) return;

    m_lbl_hdd_temperature = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_hdd_temperature")));
    if (!m_lbl_hdd_temperature) return;

    m_lbl_Mainboard_temperature = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_Mainboard_temperature")));
    if (!m_lbl_Mainboard_temperature) return;
}

void CMainFrame::Notify(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_SELECTCHANGED) {
        OnSelectChange(msg);
    }

}

void CMainFrame::OnSelectChange(TNotifyUI& msg)
{
    CDuiString name = msg.pSender->GetName();
    if (name.CompareNoCase(_T("hardware_tab")) == 0) m_pTabSwitch->SelectItem(0);
    else if(name.CompareNoCase(_T("chat_tab")) == 0) m_pTabSwitch->SelectItem(1);
    else if(name.CompareNoCase(_T("music_tab")) == 0) m_pTabSwitch->SelectItem(2);
    else if(name.CompareNoCase(_T("video_tab")) == 0) m_pTabSwitch->SelectItem(3);
    else if(name.CompareNoCase(_T("app_tab")) == 0) m_pTabSwitch->SelectItem(4);
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_TIMER:
    {
        switch (wParam)
        {
        case WM_TIMER_QUERY_CPU_USAGE:
            OnTimerQueryHardwareInfo();
            break;
        default:
            break;
        }
        break;
    }
    case WM_CUSTOM_REFRESH_HARDWARE_INFO:
        OnRefreshHardwareInfo();
        break;
    case WM_CUSTOM_INIT_HARDWARE_MONITOR_SUCCESS:
    {
		SetTimer(GetHWND(), WM_TIMER_QUERY_CPU_USAGE, 1000, NULL);
        break;
    }
    default:
        break;
    }
    return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

CControlUI* CMainFrame::CreateControl(LPCTSTR pstrClass)
{
    if (lstrcmpi(pstrClass, _T("CircleProgress")) == 0) {
        return new CCircleProgressUI();
    }
    return NULL;
}

void CMainFrame::MonitorThreadCallback()
{
    // ��ȡCPUռ����
    m_CpuUsage.SetUseCPUTimes(false);
    m_iCpuUsage = m_CpuUsage.GetCPUUsage();
    // ��ȡ�ڴ�ռ����
    m_iMemoryUsage = m_MemoryUsage.GetMemoryUsage();
    // 
    if (m_pMonitor)
    {
        m_pMonitor->GetHardwareInfo();
        // ��ȡCPUƵ��
        m_fCpuFreq = m_pMonitor->CpuFreq();
        // ��ȡCPU�¶�
        m_fCpuTemperature = m_pMonitor->CpuTemperature();
        // ��ȡGPUռ����
        m_fGpuUsage = m_pMonitor->GpuUsage();
        // ��ȡGPU�¶�
        m_fGpuTemperature = m_pMonitor->GpuTemperature();
        // ��ȡӲ���¶�
        m_fHDDTemperature = m_pMonitor->HDDTemperature();
        // ��ȡ�����¶�
        m_fMainboardTemperature = m_pMonitor->MainboardTemperature();
        m_pMonitor->AllHDDUsage();
        m_pMonitor->AllCpuTemperature();

    }
    SendMessage(WM_CUSTOM_REFRESH_HARDWARE_INFO, 0, 0);
    SetTimer(GetHWND(), WM_TIMER_QUERY_CPU_USAGE, 1000, NULL);
}

void CMainFrame::OnRefreshHardwareInfo()
{
    TCHAR wszText[260]{};
    CHAR szText[260]{};
    wsprintf(wszText, L"CPU Usage: %d\%%", (int)m_iCpuUsage);
    //m_lbl_cpu_usage->SetText(wszTexs);
    m_circle_cpu_usage->SetValue((int)m_iCpuUsage);
    m_circle_cpu_usage->SetText(wszText);

    sprintf(szText, "CPU Freq: %.2f GHz", m_fCpuFreq);
    m_lbl_cpu_freq->SetText(CCommon::StrToUnicode(szText).c_str());

    sprintf(szText, "CPU Temperature: %.2f ��", m_fCpuTemperature);
    m_lbl_cpu_temperature->SetText(CCommon::StrToUnicode(szText).c_str());

    sprintf(szText, "GPU Usage: %.2f", m_fGpuUsage);
    m_lbl_gpu_usage->SetText(CCommon::StrToUnicode(szText).c_str());

    sprintf(szText, "GPU Temperature: %.2f ��", m_fGpuTemperature);
    m_lbl_gpu_temperature->SetText(CCommon::StrToUnicode(szText).c_str());

    wsprintf(wszText, L"Memory Usage: %d\%%", (int)m_iMemoryUsage);
    m_lbl_memory_usage->SetText(wszText);

    sprintf(szText, "HDD Temperature: %.2f ��", m_fHDDTemperature);
    m_lbl_hdd_temperature->SetText(CCommon::StrToUnicode(szText).c_str());

    sprintf(szText, "Mainboard Temperature: %.2f ��", m_fMainboardTemperature);
    m_lbl_Mainboard_temperature->SetText(CCommon::StrToUnicode(szText).c_str());
}

void CMainFrame::OnTimerQueryHardwareInfo()
{
    KillTimer(GetHWND(), WM_TIMER_QUERY_CPU_USAGE);
    std::thread t(&CMainFrame::MonitorThreadCallback, this);
    t.detach();
}

void CMainFrame::InitOpenHardwareMonitor()
{
    std::thread([&] {
        m_pMonitor = OpenHardwareMonitorApi::CreateInstance();
        m_pMonitor->SetCpuEnable(true);
        m_pMonitor->SetGpuEnable(true);
        m_pMonitor->SetHddEnable(true);
        m_pMonitor->SetMainboardEnable(true);
        PostMessage(WM_CUSTOM_INIT_HARDWARE_MONITOR_SUCCESS, 0, 0);
        }).detach();
}

