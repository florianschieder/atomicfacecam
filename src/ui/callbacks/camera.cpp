#include "pch.h"
#include "AtomicFaceCam.h"

using namespace AtomicFaceCam;


HWND initializeCameraHandle(
    const AppState* appState, HWND mainWindowHandle) noexcept
{
    auto cameraHandle = capCreateCaptureWindow(
        appState->mainWindowClass,
        WS_VISIBLE + WS_CHILD,
        0,
        0,
        appState->mainWindowWidth,
        appState->mainWindowHeight,
        // we cannot use appState->mainWindowHandle because it is not
        // yet initialized here.
        mainWindowHandle,
        0);
    const auto previewRate = 1000 / appState->cameraFPSRate;

    SendMessage(cameraHandle, WM_CAP_DRIVER_CONNECT, 0, 0);
    SendMessage(cameraHandle, WM_CAP_SET_SCALE, 1, 0);
    SendMessage(cameraHandle, WM_CAP_SET_PREVIEWRATE, previewRate, 0);
    SendMessage(cameraHandle, WM_CAP_SET_PREVIEW, 1, 0);

    return cameraHandle;
}


void setInitialWindowPosition(
    const AppState* appState, HWND mainWindowHandle) noexcept
{
    SetWindowPos(
        // we cannot use appState->mainWindowHandle because it is not
        // yet initialized here.
        mainWindowHandle,
        HWND_TOPMOST,
        0,
        0,
        appState->mainWindowWidth,
        appState->mainWindowHeight,
        SWP_SHOWWINDOW);
}

enum XAxis { Left, Center, Right };
enum YAxis { Top, Middle, Bottom};

struct FixedPositionDescriptor {
    XAxis x;
    YAxis y;

    POINT calcAbsoluteCoordinates(const AppState* appState) const noexcept {
        return {
            .x = this->getAbsoluteX(appState),
            .y = this->getAbsoluteY(appState),
        };
    }

    private:
        long getAbsoluteX(const AppState *appState) const noexcept {
            const auto maxX = appState->desktopWidth - appState->mainWindowWidth;
            switch (this->x) {
                case XAxis::Left: return 0;
                case XAxis::Center: return maxX / 2;
                case XAxis::Right: return maxX;
            }
            return -1; // unreachable
        }

        long getAbsoluteY(const AppState *appState) const noexcept {
            const auto maxY = appState->desktopHeight - appState->mainWindowHeight;
            switch (this->y) {
                case YAxis::Top: return 0;
                case YAxis::Middle: return maxY / 2;
                case YAxis::Bottom: return maxY;
            }
            return -1; // unreachable
        }
};

void updateWindowPositionByNumPad(AppState* appState, UINT key)
{
    const std::map<UINT, FixedPositionDescriptor> descriptors = {
        {VK_NUMPAD1, { XAxis::Left, YAxis::Bottom}},
        {VK_NUMPAD2, { XAxis::Center, YAxis::Bottom}},
        {VK_NUMPAD3, { XAxis::Right, YAxis::Bottom}},
        {VK_NUMPAD4, { XAxis::Left, YAxis::Middle}},
        {VK_NUMPAD5, { XAxis::Center, YAxis::Middle}},
        {VK_NUMPAD6, { XAxis::Right, YAxis::Middle}},
        {VK_NUMPAD7, { XAxis::Left, YAxis::Top}},
        {VK_NUMPAD8, { XAxis::Center, YAxis::Top}},
        {VK_NUMPAD9, { XAxis::Right, YAxis::Top}},
    };
    const auto& descriptor = descriptors.at(key);
    const auto point = descriptor.calcAbsoluteCoordinates(appState);

    SetWindowPos(
        appState->mainWindowHandle,
        HWND_TOPMOST,
        point.x,
        point.y,
        appState->mainWindowWidth,
        appState->mainWindowHeight,
        SWP_SHOWWINDOW);
}


void moveWindowByArrowStep(AppState* appState, UINT key) noexcept
{
    const auto delta = (key == VK_UP || key == VK_LEFT)
                       ? -appState->pixelsToMove
                       : appState->pixelsToMove;

    RECT rect;
    GetWindowRect(appState->mainWindowHandle, &rect);

    if (key == VK_LEFT || key == VK_RIGHT) {
        rect.left += delta;
    } else {
        rect.top += delta;
    }

    SetWindowPos(
        appState->mainWindowHandle,
        HWND_TOPMOST,
        rect.left,
        rect.top,
        appState->mainWindowWidth,
        appState->mainWindowHeight,
        SWP_SHOWWINDOW);
}


void spawnHelpDialog(const AppState *appState) noexcept
{
    DialogBox(
        appState->hInstance,
        MAKEINTRESOURCE(IDD_HELP),
        appState->mainWindowHandle,
        UI::Callbacks::standardDialog);
}


void spawnConfigDialog(const AppState *appState) noexcept
{
    DialogBoxParamW(
        appState->hInstance,
        MAKEINTRESOURCE(IDD_CONFIGURATION),
        appState->mainWindowHandle,
        UI::Callbacks::configurationDialog,
        (LPARAM) &appState);
}


void spawnAboutDialog(const AppState *appState) noexcept
{              
    DialogBox(
        appState->hInstance,
        MAKEINTRESOURCE(IDD_ABOUT),
        appState->mainWindowHandle,
        UI::Callbacks::standardDialog);
}


void handlePressedKey(AppState* appState, UINT key)
{
    if (key == VK_ESCAPE) {
        DestroyWindow(appState->mainWindowHandle);
    }
    else if (key >= VK_NUMPAD1 && key <= VK_NUMPAD9) {
        updateWindowPositionByNumPad(appState, key);
    }
    else if (key == VK_UP || (key == VK_DOWN)
             || (key == VK_LEFT) || (key == VK_RIGHT)) {
        moveWindowByArrowStep(appState, key);
    }
    else if (key == VK_F1) {
        spawnHelpDialog(appState);
    }
    else if (key == VK_F2) {
        spawnConfigDialog(appState);
    }
    else if (key == VK_F3) {
        spawnAboutDialog(appState);
    }
}


LRESULT CALLBACK UI::Callbacks::mainWindow(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto appState = getAppState(hWnd, message, lParam);
    switch (message)
    {
        case WM_KEYDOWN:
            handlePressedKey(appState, (UINT) wParam);
            break;

        case WM_CREATE:
            appState->cameraControlHandle =
                initializeCameraHandle(appState, hWnd);
            setInitialWindowPosition(appState, hWnd);
            break;

        case WM_DESTROY:
            SendMessage(
                appState->cameraControlHandle, WM_CAP_DRIVER_DISCONNECT, 0, 0);
            PostQuitMessage(0);
            return 0;

        default:
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}