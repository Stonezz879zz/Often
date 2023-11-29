// Often.cpp : 定义应用程序的入口点。
//
#include "resource.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<crtdbg.h>
#include "UI/MainFrame.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 初始化UI管理器
    CPaintManagerUI::SetInstance(hInstance);
    CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
    strResourcePath += _T("skin\\res\\");
    CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
    CMainFrame* pMainWnd = new CMainFrame();
    if (pMainWnd == NULL) return 0;
    HWND hWnd = pMainWnd->Create(NULL, _T("test"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
    pMainWnd->CenterWindow();
    ::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE);
    // 消息循环
    CPaintManagerUI::MessageLoop();
    // 销毁窗口
    delete pMainWnd;
    pMainWnd = NULL;
    // 清理资源
    CPaintManagerUI::Term();
    

}
