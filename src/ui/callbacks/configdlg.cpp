#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


INT_PTR CALLBACK UI::Callbacks::configurationDialog(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    auto application = retrieveAppInstance(hwnd, Message, lParam);
    switch (Message)
    {
    case WM_INITDIALOG:
        CheckDlgButton(
            hwnd,
            IDC_RADIO320240,
            (application->mainWindowWidth == 320
             && application->mainWindowHeight == 240));

        CheckDlgButton(
            hwnd,
            IDC_RADIO640480,
            (application->mainWindowWidth == 640
             && application->mainWindowHeight == 480));

        SetDlgItemInt(
            hwnd,
            IDC_ARROWSTEP,
            application->pixelsToMove,
            TRUE);

        SetDlgItemInt(
            hwnd,
            IDC_FPS,
            application->cameraFPSRate,
            TRUE);

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            if (IsDlgButtonChecked(hwnd, IDC_RADIO320240))
            {
                application->mainWindowWidth = 320;
                application->mainWindowHeight = 240;
            } else if (IsDlgButtonChecked(hwnd, IDC_RADIO640480))
            {
                application->mainWindowWidth = 640;
                application->mainWindowHeight = 480;
            }

            application->pixelsToMove = GetDlgItemInt(hwnd, IDC_ARROWSTEP, NULL, TRUE);
            application->cameraFPSRate = GetDlgItemInt(hwnd, IDC_FPS, NULL, TRUE);

            Config::save(*application);

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
