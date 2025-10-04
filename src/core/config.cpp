#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


void Config::loadInto(App& application)
{
    DWORD bufferSize = 4;

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraArrowKeyStep",
        RRF_RT_DWORD,
        NULL,
        (PVOID) &application.pixelsToMove,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraHeight",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.mainWindowHeight,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraWidth",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.mainWindowWidth,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraFPSRate",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.cameraFPSRate,
        &bufferSize);
}

void Config::Save(const App& application)
{
    DWORD bufferSize = 4;

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraArrowKeyStep",
        REG_DWORD,
        (LPVOID) &application.pixelsToMove,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraWidth",
        REG_DWORD,
        (LPVOID) &application.mainWindowWidth,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraHeight",
        REG_DWORD,
        (LPVOID) &application.mainWindowHeight,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraFPSRate",
        REG_DWORD,
        (LPVOID) &application.cameraFPSRate,
        bufferSize);
}