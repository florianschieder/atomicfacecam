#pragma once

#include "../res/Resource.h"
#include "pch.h"

namespace AtomicFaceCam
{
    struct AppState
    {
        HINSTANCE hInstance;
        int nCmdShow;
        HWND mainWindowHandle;
        HWND cameraControlHandle;

        LPCTSTR mainWindowTitle;
        LPCTSTR mainWindowClass;
        LPCTSTR cameraControlClass;

        int mainWindowWidth;
        int mainWindowHeight;
        int cameraFPSRate;

        int desktopWidth;
        int desktopHeight;

        int pixelsToMove;
    };

    int Main(AppState&);

    namespace Config {
        void loadInto(AppState&) noexcept;
        void save(const AppState&) noexcept;
    }

    namespace UI {
        void initializeCommonControls() noexcept;
        ATOM registerMainWindow(const AppState&) noexcept;
        void initializeMainWindow(AppState&) noexcept;
        AppState* getAppState(HWND hWnd, UINT message, LPARAM lParam) noexcept;

        namespace Callbacks {
            LRESULT CALLBACK mainWindow(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK standardDialog(HWND, UINT, WPARAM, LPARAM) noexcept;
            INT_PTR CALLBACK configurationDialog(HWND, UINT, WPARAM, LPARAM) noexcept;
        }
    }
}