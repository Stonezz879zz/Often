#include "MainFrame.h"
#include "MessageDefine.h"
#include <thread>
CMainFrame::CMainFrame()
    : m_lbl_cpu_usage(nullptr)
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
    m_lbl_cpu_usage = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_cpu_usage")));
    if (!m_lbl_cpu_usage) return;
    m_lbl_cpu_usage->SetText(L"test");
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
        wsprintf(wszTexs, L"CPU: %d\%", (int)lParam);
        m_lbl_cpu_usage->SetText(wszTexs);
        break;
    }
    default:
        break;
    }
    return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

void CMainFrame::MonitorThreadCallback()
{
    m_CpuUsage.SetUseCPUTimes(false);
    //m_CpuUsage.GetCPUUsage();
    PostMessage(WM_REFRESH_CPU_USAGE, 0, m_CpuUsage.GetCPUUsage());
}
