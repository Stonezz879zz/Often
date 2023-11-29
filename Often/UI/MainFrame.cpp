#include "MainFrame.h"
#include "MessageDefine.h"
#include <thread>
CMainFrame::CMainFrame()
    : m_lbl_cpu_usage(nullptr),
    m_circle_cpu_usage(nullptr),
    m_iCpuUsage(0),
    m_iMemoryUsage(0)
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
    m_circle_cpu_usage = static_cast<CCircleProgressUI*>(m_pm.FindControl(_T("circle_cpu_usage")));
    if (!m_circle_cpu_usage) return;
    m_circle_cpu_usage->SetCenterColor(m_circle_cpu_usage->GetBkColor());
    m_lbl_cpu_usage = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_cpu_usage")));
    if (!m_lbl_cpu_usage) return;
    m_lbl_cpu_usage->SetText(L"Often");
    SetTimer(GetHWND(), WM_TIMER_QUERY_CPU_USAGE, 1000, NULL);
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_TIMER:
    {
        if (wParam == WM_TIMER_QUERY_CPU_USAGE)
        {
            std::thread t(&CMainFrame::MonitorThreadCallback, this);
            t.detach();
        }
        
        break;
    }
    case WM_REFRESH_CPU_USAGE:
    {
        TCHAR wszTexs[260]{};
        wsprintf(wszTexs, L"CPU: %d\%%", (int)m_iCpuUsage);
        //m_lbl_cpu_usage->SetText(wszTexs);
        m_circle_cpu_usage->SetValue((int)m_iCpuUsage);
        m_circle_cpu_usage->SetText(wszTexs);
        wsprintf(wszTexs, L"Memory: %d\%%", (int)m_iMemoryUsage );
        m_lbl_cpu_usage->SetText(wszTexs);
        
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
    m_CpuUsage.SetUseCPUTimes(false);
    m_iCpuUsage = m_CpuUsage.GetCPUUsage();
    
    m_iMemoryUsage = m_MemoryUsage.GetMemoryUsage();
    //m_CpuUsage.GetCPUUsage();
    PostMessage(WM_REFRESH_CPU_USAGE, 0, 0);
}

