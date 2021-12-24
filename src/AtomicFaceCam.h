#pragma once

#include "resource.h"
#include "pch.h"
#include "Hibernation.h"

struct Resolution
{
    unsigned short int width;
    unsigned short int height;
};

struct AFCConfig
{
    Resolution resolution;
    unsigned char fpsRate;          // 0 <= fpsRate <= 255
    unsigned short int moveAmount;  // 0 <= moveAmount <= 65535
};

struct AFCApp
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

    AFCConfig config;

    int desktopWidth = 0;
    int desktopHeight = 0;
};

namespace AtomicFaceCam
{
    ATOM MyRegisterClass();
    BOOL InitInstance(int);

    int Main();
    LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

    INT_PTR CALLBACK HelpDlgProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK ConfigurationDlgProc(HWND, UINT, WPARAM, LPARAM);
}