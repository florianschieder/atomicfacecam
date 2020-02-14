#pragma once

#include "resource.h"
#include "framework.h"

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
    int standardPosition = 7;
    int arrowStep = 10;
};

namespace AtomicFaceCam
{
    ATOM MyRegisterClass();
    BOOL InitInstance(int);
    int Main();
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}