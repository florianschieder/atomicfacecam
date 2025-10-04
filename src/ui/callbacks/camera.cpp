#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


LRESULT CALLBACK UI::Callbacks::MainWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto application = RetrieveAppInstance(hWnd, message, lParam);
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
                        application->desktopHeight - application->hMainWndHeight,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD2:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (application->desktopWidth - application->hMainWndWidth) / 2,
                        application->desktopHeight - application->hMainWndHeight,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD3:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        application->desktopWidth - application->hMainWndWidth,
                        application->desktopHeight - application->hMainWndHeight,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD4:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        (application->desktopHeight - application->hMainWndHeight) / 2,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD5:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (application->desktopWidth - application->hMainWndWidth) / 2,
                        (application->desktopHeight - application->hMainWndHeight) / 2,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD6:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        application->desktopWidth - application->hMainWndWidth,
                        (application->desktopHeight - application->hMainWndHeight) / 2,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD7:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        0,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD8:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (application->desktopWidth - application->hMainWndWidth) / 2,
                        0,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD9:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        application->desktopWidth - application->hMainWndWidth,
                        0,
                        application->hMainWndWidth,
                        application->hMainWndHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_UP:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.top -= application->arrowStep;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application->hMainWndWidth,
                            application->hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_DOWN:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.top += application->arrowStep;

                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application->hMainWndWidth,
                            application->hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_LEFT:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.left -= application->arrowStep;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application->hMainWndWidth,
                            application->hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_RIGHT:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.left += application->arrowStep;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            application->hMainWndWidth,
                            application->hMainWndHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_F1:
                    DialogBox(
                        application->hInstance,
                        MAKEINTRESOURCE(IDD_HELP),
                        hWnd,
                        Callbacks::StandardDialog);
                    break;

                case VK_F2:
                    DialogBoxParamW(
                        application->hInstance,
                        MAKEINTRESOURCE(IDD_CONFIGURATION),
                        hWnd,
                        Callbacks::ConfigurationDialog,
                        (LPARAM) &application);
                    break;

                case VK_F3:
                    DialogBox(
                        application->hInstance,
                        MAKEINTRESOURCE(IDD_ABOUT),
                        hWnd,
                        Callbacks::StandardDialog);
                    break;
            }
            break;

        case WM_CREATE:
            application->hWebCam = capCreateCaptureWindow(
                application->szMainWindowClass,
                WS_VISIBLE + WS_CHILD,
                0,
                0,
                application->hMainWndWidth,
                application->hMainWndHeight,
                hWnd,
                0);

            SendMessage(
                application->hWebCam,
                WM_CAP_DRIVER_CONNECT,
                0,
                0);

            SendMessage(
               application->hWebCam,
                WM_CAP_SET_SCALE,
                1,
                0);

            SendMessage(
                application->hWebCam,
                WM_CAP_SET_PREVIEWRATE,
                1000 / application->fpsRate,
                0);

            SendMessage(
                application->hWebCam,
                WM_CAP_SET_PREVIEW,
                1,
                0);

            SetWindowPos(
                hWnd,
                HWND_TOPMOST,
                0,
                0,
                application->hMainWndWidth,
                application->hMainWndHeight,
                SWP_SHOWWINDOW);

            break;

        case WM_DESTROY:
            SendMessage(
                application->hWebCam,
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