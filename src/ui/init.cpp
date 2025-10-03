#include "pch.h"

#include <AtomicFaceCam.h>

using namespace AtomicFaceCam;


ATOM UI::MyRegisterClass(const AppWithDefaults& application)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = UI::Callbacks::MainWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = application.hInstance;
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = application.szMainWindowClass;

    wcex.hCursor = LoadCursor(
        application.hInstance,
        IDC_ARROW);

    wcex.hIcon = LoadIcon(
        application.hInstance,
        MAKEINTRESOURCE(IDI_ATOMICFACECAM));

    wcex.hIconSm = LoadIcon(
        application.hInstance,
        MAKEINTRESOURCE(IDI_ATOMICFACECAM));

    return RegisterClassExW(&wcex);
}

BOOL UI::InitInstance(AppWithDefaults& application)
{
    application.hMainWnd = CreateWindowW(
        application.szMainWindowClass,
        application.szTitle,
        WS_POPUP | WS_VISIBLE | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        application.hMainWndWidth,
        application.hMainWndHeight,
        NULL,
        NULL,
        application.hInstance,
        NULL);

    if (!application.hMainWnd)
    {
      return FALSE;
    }

    ShowWindow(
        application.hMainWnd,
        application.nCmdShow);

    UpdateWindow(application.hMainWnd);

    return TRUE;
}

void AtomicFaceCam::UI::InitializeCommonControls()
{
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);
}