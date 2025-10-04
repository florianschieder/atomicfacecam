#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


INT_PTR CALLBACK UI::Callbacks::ConfigurationDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    auto application = RetrieveAppInstance(hwnd, Message, lParam);
    switch (Message)
    {
    case WM_INITDIALOG:
        CheckDlgButton(
            hwnd,
            IDC_RADIO320240,
            (application->hMainWndWidth == 320
             && application->hMainWndHeight == 240));

        CheckDlgButton(
            hwnd,
            IDC_RADIO640480,
            (application->hMainWndWidth == 640
             && application->hMainWndHeight == 480));

        SetDlgItemInt(
            hwnd,
            IDC_ARROWSTEP,
            application->arrowStep,
            TRUE);

        SetDlgItemInt(
            hwnd,
            IDC_FPS,
            application->fpsRate,
            TRUE);

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            if (IsDlgButtonChecked(hwnd, IDC_RADIO320240))
            {
                application->hMainWndWidth = 320;
                application->hMainWndHeight = 240;
            } else if (IsDlgButtonChecked(hwnd, IDC_RADIO640480))
            {
                application->hMainWndWidth = 640;
                application->hMainWndHeight = 480;
            }

            application->arrowStep = GetDlgItemInt(hwnd, IDC_ARROWSTEP, NULL, TRUE);
            application->fpsRate = GetDlgItemInt(hwnd, IDC_FPS, NULL, TRUE);

            Config::Save(*application);

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
