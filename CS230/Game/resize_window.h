#pragma once
#include <Windows.h>

void make_resizable()
{
    HWND window_handle = GetActiveWindow();
    SetWindowLong(window_handle, GWL_STYLE, GetWindowLong(window_handle, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
}