#include "pch.h"

#include <AtomicFaceCam.h>

using namespace AtomicFaceCam;


ATOM UI::registerMainWindow(const App& application)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = UI::Callbacks::mainWindow;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = application.hInstance;
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = application.mainWindowClass;

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

void UI::initializeMainWindow(App& application)
{
    application.mainWindowHandle = CreateWindowExW(
        0,
        application.mainWindowClass,
        application.mainWindowTitle,
        WS_POPUP | WS_VISIBLE | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        application.mainWindowWidth,
        application.mainWindowHeight,
        NULL,
        NULL,
        application.hInstance,
        (LPVOID) &application);

    ShowWindow(application.mainWindowHandle, application.nCmdShow);
    UpdateWindow(application.mainWindowHandle);
}

void AtomicFaceCam::UI::initializeCommonControls()
{
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);
}