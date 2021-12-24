#include "AtomicFaceCam.h"

#include "pch.h"

using namespace AtomicFaceCam;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

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

    auto configHibernation = ConfigHibernation();
    application.config = configHibernation.load();

    return AtomicFaceCam::Main();
}