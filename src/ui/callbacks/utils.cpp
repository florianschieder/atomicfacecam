#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;

AppState* UI::getAppState(HWND hWnd, UINT message, LPARAM lParam)
{
    if (message == WM_CREATE || message == WM_INITDIALOG) {
        SetWindowLongPtr(hWnd, GWLP_USERDATA, *(LONG_PTR*) lParam);
    }
    return (AppState*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
}