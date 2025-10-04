#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;

AppWithDefaults* UI::RetrieveAppInstance(HWND hWnd, UINT message, LPARAM lParam)
{
    if (message == WM_CREATE || message == WM_INITDIALOG) {
        SetWindowLongPtr(hWnd, GWLP_USERDATA, *(LONG_PTR*) lParam);
    }
    return (AppWithDefaults*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
}