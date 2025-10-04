#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


LRESULT CALLBACK UI::Callbacks::mainWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto appState = getAppState(hWnd, message, lParam);
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
                        appState->desktopHeight - appState->mainWindowHeight,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD2:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (appState->desktopWidth - appState->mainWindowWidth) / 2,
                        appState->desktopHeight - appState->mainWindowHeight,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD3:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        appState->desktopWidth - appState->mainWindowWidth,
                        appState->desktopHeight - appState->mainWindowHeight,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD4:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        (appState->desktopHeight - appState->mainWindowHeight) / 2,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD5:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (appState->desktopWidth - appState->mainWindowWidth) / 2,
                        (appState->desktopHeight - appState->mainWindowHeight) / 2,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD6:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        appState->desktopWidth - appState->mainWindowWidth,
                        (appState->desktopHeight - appState->mainWindowHeight) / 2,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD7:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        0,
                        0,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD8:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        (appState->desktopWidth - appState->mainWindowWidth) / 2,
                        0,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_NUMPAD9:
                    SetWindowPos(
                        hWnd,
                        HWND_TOPMOST,
                        appState->desktopWidth - appState->mainWindowWidth,
                        0,
                        appState->mainWindowWidth,
                        appState->mainWindowHeight,
                        SWP_SHOWWINDOW);
                    break;

                case VK_UP:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.top -= appState->pixelsToMove;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            appState->mainWindowWidth,
                            appState->mainWindowHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_DOWN:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.top += appState->pixelsToMove;

                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            appState->mainWindowWidth,
                            appState->mainWindowHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_LEFT:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.left -= appState->pixelsToMove;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            appState->mainWindowWidth,
                            appState->mainWindowHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_RIGHT:
                    {
                        RECT rect;
                        GetWindowRect(hWnd, &rect);
                        rect.left += appState->pixelsToMove;
                        SetWindowPos(
                            hWnd,
                            HWND_TOPMOST,
                            rect.left,
                            rect.top,
                            appState->mainWindowWidth,
                            appState->mainWindowHeight,
                            SWP_SHOWWINDOW);
                    }
                    break;

                case VK_F1:
                    DialogBox(
                        appState->hInstance,
                        MAKEINTRESOURCE(IDD_HELP),
                        hWnd,
                        Callbacks::standardDialog);
                    break;

                case VK_F2:
                    DialogBoxParamW(
                        appState->hInstance,
                        MAKEINTRESOURCE(IDD_CONFIGURATION),
                        hWnd,
                        Callbacks::configurationDialog,
                        (LPARAM) &appState);
                    break;

                case VK_F3:
                    DialogBox(
                        appState->hInstance,
                        MAKEINTRESOURCE(IDD_ABOUT),
                        hWnd,
                        Callbacks::standardDialog);
                    break;
            }
            break;

        case WM_CREATE:
            appState->cameraControlHandle = capCreateCaptureWindow(
                appState->mainWindowClass,
                WS_VISIBLE + WS_CHILD,
                0,
                0,
                appState->mainWindowWidth,
                appState->mainWindowHeight,
                hWnd,
                0);

            SendMessage(
                appState->cameraControlHandle,
                WM_CAP_DRIVER_CONNECT,
                0,
                0);

            SendMessage(
               appState->cameraControlHandle,
                WM_CAP_SET_SCALE,
                1,
                0);

            SendMessage(
                appState->cameraControlHandle,
                WM_CAP_SET_PREVIEWRATE,
                1000 / appState->cameraFPSRate,
                0);

            SendMessage(
                appState->cameraControlHandle,
                WM_CAP_SET_PREVIEW,
                1,
                0);

            SetWindowPos(
                hWnd,
                HWND_TOPMOST,
                0,
                0,
                appState->mainWindowWidth,
                appState->mainWindowHeight,
                SWP_SHOWWINDOW);

            break;

        case WM_DESTROY:
            SendMessage(
                appState->cameraControlHandle,
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