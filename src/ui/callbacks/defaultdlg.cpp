#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;

INT_PTR CALLBACK UI::Callbacks::standardDialog(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    UNREFERENCED_PARAMETER(lParam);
    switch (msg)
    {
        case WM_INITDIALOG:
            return true;

        case WM_COMMAND:
        {
            const auto callback = LOWORD(wParam);
            if (callback == IDOK || callback == IDCANCEL) {
                EndDialog(hWnd, callback);
            }
            return false;
        }

        default:
            return false;
    }
}