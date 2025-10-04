#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    AppWithDefaults application;

    UI::InitializeCommonControls();

    application.hInstance = hInstance;
    application.nCmdShow = nCmdShow;

    application.szTitle = L"Atomic Face Cam";
    application.szMainWindowClass = L"AtomicFaceCamWindow";
    application.szCameraClass = L"AtomicFaceCamCamera";

    application.argv = CommandLineToArgvW(
        lpCmdLine,
        &application.argc);

    return AtomicFaceCam::Main(application);
}

int AtomicFaceCam::Main(AppWithDefaults& application)
{
    Config::Load(application);
    UI::MyRegisterClass(application);

    if (!UI::InitInstance(application))
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