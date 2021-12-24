#pragma once

#include "resource.h"
#include "pch.h"

#include "App/Config/Config.h"
#include "App/Config/Hibernation.h"

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

    Config config;

    int desktopWidth = 0;
    int desktopHeight = 0;
};

namespace AtomicFaceCam
{
    AFCApp application;

    ATOM MyRegisterClass();
    BOOL InitInstance(int);

    int Main();
    LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

    INT_PTR CALLBACK HelpDlgProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK ConfigurationDlgProc(HWND, UINT, WPARAM, LPARAM);
}