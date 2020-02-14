#include "pch.h"
#include "AtomicFaceCam.h"

AtomicFaceCamApp application;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    application.hInstance = hInstance;
    application.nCmdShow = nCmdShow;

    application.szTitle = L"Atomic Face Cam";
    application.szMainWindowClass = L"AtomicFaceCamWindow";
    application.szCameraClass = L"AtomicFaceCamCamera";

    application.argv = CommandLineToArgvW(
        lpCmdLine,
        &application.argc);

    return AtomicFaceCam::Main();
}

int AtomicFaceCam::Main()
{
    MyRegisterClass();

    if (!InitInstance(application.nCmdShow))
    {
        return FALSE;
    }

    HWND hDesktopWindow = GetDesktopWindow();
    RECT hDesktopRect = { 0 };

    GetWindowRect(hDesktopWindow, &hDesktopRect);
    application.desktopHeight = hDesktopRect.bottom - hDesktopRect.top;
    application.desktopWidth = hDesktopRect.right - hDesktopRect.left;

    MSG msg;

    while (GetMessage(
        &msg,
        NULL,
        0,
        0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

ATOM AtomicFaceCam::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
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

BOOL AtomicFaceCam::InitInstance(int nCmdShow)
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
        nCmdShow);

    UpdateWindow(application.hMainWnd);

    return TRUE;
}

LRESULT CALLBACK AtomicFaceCam::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_ESCAPE:
                    DestroyWindow(hWnd);
                    break;

                case VK_NUMPAD1:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        application.desktopHeight - application.hMainWndHeight,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD2:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (application.desktopWidth - application.hMainWndWidth) / 2,
                        application.desktopHeight - application.hMainWndHeight,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD3:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        application.desktopWidth - application.hMainWndWidth,
                        application.desktopHeight - application.hMainWndHeight,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD4:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        (application.desktopHeight - application.hMainWndHeight) / 2,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD5:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (application.desktopWidth - application.hMainWndWidth) / 2,
                        (application.desktopHeight - application.hMainWndHeight) / 2,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD6:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        application.desktopWidth - application.hMainWndWidth,
                        (application.desktopHeight - application.hMainWndHeight) / 2,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD7:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        0,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD8:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (application.desktopWidth - application.hMainWndWidth) / 2,
                        0,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD9:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        application.desktopWidth - application.hMainWndWidth,
                        0,
                        application.hMainWndWidth,
                        application.hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_UP:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.top -= application.arrowStep;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application.hMainWndWidth,
                            application.hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_DOWN:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.top += application.arrowStep;

                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application.hMainWndWidth,
                            application.hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_LEFT:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.left -= application.arrowStep;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application.hMainWndWidth,
                            application.hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_RIGHT:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.left += application.arrowStep;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application.hMainWndWidth,
                            application.hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;
            }
            break;

        case WM_CREATE:
            application.hWebCam = capCreateCaptureWindow(
                application.szMainWindowClass,
                WS_VISIBLE + WS_CHILD,
                0,
                0,
                application.hMainWndWidth,
                application.hMainWndHeight,
                hWnd,
                0);

            SendMessage(
                application.hWebCam,
                WM_CAP_DRIVER_CONNECT,
                0,
                0);

            SendMessage(
               application.hWebCam,
                WM_CAP_SET_SCALE,
                1,
                0);

            SendMessage(
                application.hWebCam,
                WM_CAP_SET_PREVIEWRATE,
                1000 / application.fpsRate,
                0);

            SendMessage(
                application.hWebCam,
                WM_CAP_SET_PREVIEW,
                1,
                0);

            SetWindowPos(
                hWnd,
                HWND_TOPMOST,
                0,
                0,
                application.hMainWndWidth,
                application.hMainWndHeight,
                SWP_SHOWWINDOW);

            break;

        case WM_DESTROY:
            SendMessage(
                application.hWebCam,
                WM_CAP_DRIVER_DISCONNECT,
                0,
                0);

            PostQuitMessage(0);
            return 0;

        default:
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
