#pragma once

#include "resource.h"
#include "pch.h"

struct AtomicFaceCamApp
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

namespace AtomicFaceCam
{
    ATOM MyRegisterClass();
    BOOL InitInstance(int);
    void LoadConfiguration();
    void SaveConfiguration();

    int Main();
    LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

    INT_PTR CALLBACK HelpDlgProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK ConfigurationDlgProc(HWND, UINT, WPARAM, LPARAM);
}