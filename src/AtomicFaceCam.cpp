#include "pch.h"
#include "AtomicFaceCam.h"

AtomicFaceCamApp application;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES;

    InitCommonControlsEx(&icc);

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

void AtomicFaceCam::LoadConfiguration()
{
    DWORD bufferSize = 4;

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraArrowKeyStep",
        RRF_RT_DWORD,
        NULL,
        (PVOID) &application.arrowStep,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraHeight",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.hMainWndHeight,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraWidth",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.hMainWndWidth,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraFPSRate",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.fpsRate,
        &bufferSize);
}

void AtomicFaceCam::SaveConfiguration()
{
    DWORD bufferSize = 4;

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraArrowKeyStep",
        REG_DWORD,
        (LPVOID) &application.arrowStep,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraWidth",
        REG_DWORD,
        (LPVOID) &application.hMainWndWidth,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraHeight",
        REG_DWORD,
        (LPVOID) &application.hMainWndHeight,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraFPSRate",
        REG_DWORD,
        (LPVOID) &application.fpsRate,
        bufferSize);
}

int AtomicFaceCam::Main()
{
    LoadConfiguration();
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
    wcex.lpfnWndProc = MainWndProc;
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

LRESULT CALLBACK AtomicFaceCam::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

                case VK_F1:
                    DialogBox(
                        application.hInstance,
                        MAKEINTRESOURCE(IDD_HELP),
                        hWnd,
                        HelpDlgProc);
                    break;

                case VK_F2:
                    DialogBox(
                        application.hInstance,
                        MAKEINTRESOURCE(IDD_CONFIGURATION),
                        hWnd,
                        ConfigurationDlgProc);
                    break;

                case VK_F3:
                    DialogBox(
                        application.hInstance,
                        MAKEINTRESOURCE(IDD_ABOUT),
                        hWnd,
                        AboutDlgProc);
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

INT_PTR CALLBACK AtomicFaceCam::AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hwnd, IDOK);
            break;
        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

INT_PTR CALLBACK AtomicFaceCam::HelpDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_INITDIALOG:

        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hwnd, IDOK);
            break;
        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

INT_PTR CALLBACK AtomicFaceCam::ConfigurationDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_INITDIALOG:
        CheckDlgButton(
            hwnd,
            IDC_RADIO320240,
            (application.hMainWndWidth == 320 && application.hMainWndHeight == 240));

        CheckDlgButton(
            hwnd,
            IDC_RADIO640480,
            (application.hMainWndWidth == 640 && application.hMainWndHeight == 480));

        SetDlgItemInt(
            hwnd,
            IDC_ARROWSTEP,
            application.arrowStep,
            TRUE);

        SetDlgItemInt(
            hwnd,
            IDC_FPS,
            application.fpsRate,
            TRUE);

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            if (IsDlgButtonChecked(hwnd, IDC_RADIO320240))
            {
                application.hMainWndWidth = 320;
                application.hMainWndHeight = 240;
            } else if (IsDlgButtonChecked(hwnd, IDC_RADIO640480))
            {
                application.hMainWndWidth = 640;
                application.hMainWndHeight = 480;
            }

            application.arrowStep = GetDlgItemInt(hwnd, IDC_ARROWSTEP, NULL, TRUE);
            application.fpsRate = GetDlgItemInt(hwnd, IDC_FPS, NULL, TRUE);

            SaveConfiguration();

            EndDialog(hwnd, IDOK);
            break;
        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}
