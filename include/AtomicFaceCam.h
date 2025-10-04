#pragma once

#include "../res/Resource.h"
#include "pch.h"

namespace AtomicFaceCam
{
    struct AppWithDefaults
    {
        HINSTANCE hInstance = NULL;
        int nCmdShow = SW_SHOW;
        HWND hMainWnd = NULL;
        HWND hWebCam = NULL;

        int argc = 0;
        WCHAR** argv = NULL;

        LPCTSTR szTitle = L"";
        LPCTSTR szMainWindowClass = L"";
        LPCTSTR szCameraClass = L"";

        int hMainWndWidth = 320;
        int hMainWndHeight = 240;
        int fpsRate = 20;

        int desktopWidth = 0;
        int desktopHeight = 0;

        int arrowStep = 10;
    };

    int Main(AppWithDefaults&);

    namespace Config {
        void Load(const AppWithDefaults&);
        void Save(const AppWithDefaults&);
    }

    namespace UI {
        void InitializeCommonControls();
        ATOM MyRegisterClass(const AppWithDefaults&);
        BOOL InitInstance(AppWithDefaults&);
        AppWithDefaults* RetrieveAppInstance(HWND hWnd, UINT message, LPARAM lParam);

        namespace Callbacks {
            LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

            INT_PTR CALLBACK HelpDlgProc(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
            INT_PTR CALLBACK ConfigurationDlgProc(HWND, UINT, WPARAM, LPARAM);
        }
    }
}