#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


void initializeConfigDialog(
    HWND hWnd, const AppState * const appState) noexcept
{
    const auto lowResolutionChecked =
        appState->mainWindowWidth == 320
        && appState->mainWindowHeight == 240;
    const auto highResolutionChecked =
        appState->mainWindowWidth == 640
        && appState->mainWindowHeight == 480;

    CheckDlgButton(hWnd, IDC_RADIO320240, lowResolutionChecked);
    CheckDlgButton(hWnd, IDC_RADIO640480, highResolutionChecked);
    SetDlgItemInt(hWnd, IDC_ARROWSTEP, appState->pixelsToMove, true);
    SetDlgItemInt(hWnd, IDC_FPS, appState->cameraFPSRate, true);
}


void reflectConfigurationIntoAppState(
    HWND hWnd, AppState * const appState) noexcept
{
    if (IsDlgButtonChecked(hWnd, IDC_RADIO320240)) {
        appState->mainWindowWidth = 320;
        appState->mainWindowHeight = 240;
    }
    else if (IsDlgButtonChecked(hWnd, IDC_RADIO640480)) {
        appState->mainWindowWidth = 640;
        appState->mainWindowHeight = 480;
    }
    appState->pixelsToMove = GetDlgItemInt(hWnd, IDC_ARROWSTEP, NULL, true);
    appState->cameraFPSRate = GetDlgItemInt(hWnd, IDC_FPS, NULL, true);
}

void reflectConfigurationIntoAppStateOnOK(
    HWND hWnd, WPARAM wParam, AppState * appState) noexcept
{
    if (LOWORD(wParam) == IDOK && appState != NULL) {
        reflectConfigurationIntoAppState(hWnd, appState);
        Config::save(*appState);
    }
}

void closeDialogIfTriggered(HWND hWnd, WPARAM wParam) noexcept
{
    const auto command = LOWORD(wParam);
    if (command == IDOK || command == IDCANCEL) {
        EndDialog(hWnd, command);
    }
}

INT_PTR CALLBACK UI::Callbacks::configurationDialog(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    auto appState = getAppState(hWnd, msg, lParam);
    switch (msg)
    {
        case WM_INITDIALOG:
            initializeConfigDialog(hWnd, appState);
            return true;

        case WM_COMMAND:
            reflectConfigurationIntoAppStateOnOK(hWnd, wParam, appState);
            closeDialogIfTriggered(hWnd, wParam);
            return true;

        default:
            return false;
    }
}
