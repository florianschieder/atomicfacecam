#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


void initializeUIArtifacts(const AppState& application)
{
    UI::initializeCommonControls();
    UI::registerMainWindow(application);
}

void applyDesktopDimensions(AppState& application)
{
    const auto hDesktopWindow = GetDesktopWindow();

    RECT hDesktopRect;
    GetWindowRect(hDesktopWindow, &hDesktopRect);

    application.desktopHeight = hDesktopRect.bottom - hDesktopRect.top;
    application.desktopWidth = hDesktopRect.right - hDesktopRect.left;
}


int enterMainLoop()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AppState application = {
        .hInstance = hInstance,
        .nCmdShow = nCmdShow,

        .mainWindowTitle = L"Atomic Face Cam",
        .mainWindowClass = L"AtomicFaceCamWindow",
        .cameraControlClass = L"AtomicFaceCamCamera",
    };

    initializeUIArtifacts(application);
    applyDesktopDimensions(application);
    Config::loadInto(application);

    UI::initializeMainWindow(application);

    return enterMainLoop();
}