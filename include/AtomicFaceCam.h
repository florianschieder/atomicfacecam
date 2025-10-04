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
        void Save(const App&);
    }

    namespace UI {
        void InitializeCommonControls();
        ATOM RegisterMainWindow(const App&);
        void InitializeMainWindow(App&);
        App* RetrieveAppInstance(HWND hWnd, UINT message, LPARAM lParam);

        namespace Callbacks {
            LRESULT CALLBACK MainWindow(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK StandardDialog(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK ConfigurationDialog(HWND, UINT, WPARAM, LPARAM);
        }
    }
}