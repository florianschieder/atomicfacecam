#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


void Config::Load(const AppWithDefaults& application)
{
    DWORD bufferSize = 4;

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraArrowKeyStep",
        RRF_RT_DWORD,
        NULL,
        (PVOID) &application.arrowStep,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraHeight",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.hMainWndHeight,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraWidth",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.hMainWndWidth,
        &bufferSize);

    RegGetValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraFPSRate",
        RRF_RT_DWORD,
        NULL,
        (PVOID)&application.fpsRate,
        &bufferSize);
}

void Config::Save(const AppWithDefaults& application)
{
    DWORD bufferSize = 4;

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraArrowKeyStep",
        REG_DWORD,
        (LPVOID) &application.arrowStep,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraWidth",
        REG_DWORD,
        (LPVOID) &application.hMainWndWidth,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraHeight",
        REG_DWORD,
        (LPVOID) &application.hMainWndHeight,
        bufferSize);

    RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"SOFTWARE\\AtomicFaceCam\\",
        L"CameraFPSRate",
        REG_DWORD,
        (LPVOID) &application.fpsRate,
        bufferSize);
}