#pragma once

#include "../res/Resource.h"
#include "pch.h"

namespace AtomicFaceCam
{
    struct App
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

    int Main(App&);

    namespace Config {
        void loadInto(App&);
        void save(const App&);
    }

    namespace UI {
        void initializeCommonControls();
        ATOM registerMainWindow(const App&);
        void initializeMainWindow(App&);
        App* retrieveAppInstance(HWND hWnd, UINT message, LPARAM lParam);

        namespace Callbacks {
            LRESULT CALLBACK mainWindow(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK standardDialog(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK configurationDialog(HWND, UINT, WPARAM, LPARAM);
        }
    }
}