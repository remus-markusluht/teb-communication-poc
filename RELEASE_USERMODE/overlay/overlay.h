#pragma once
#include "../Includes.h"

#pragma once
#include <Windows.h>  
#include <iostream>
#include <d3d11.h>
#include <dwmapi.h>
#include <chrono>
#include <thread>

inline ID3D11Device* p_device = nullptr;
inline ID3D11DeviceContext* d3d_device_ctx = nullptr;
inline IDXGISwapChain* d3d_swap_chain = nullptr;
inline ID3D11RenderTargetView* d3d_render_target = nullptr;

inline MSG messager = { NULL };
inline HWND my_wnd = NULL;
inline RECT GameRect = { NULL };

inline HWND GameWnd = NULL;

inline DWORD ScreenCenterX2;
inline DWORD ScreenCenterY2;

static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;

static ULONG Width = GetSystemMetrics(SM_CXSCREEN);
static ULONG Height = GetSystemMetrics(SM_CYSCREEN);


auto get_process_wnd(uint32_t pid) -> HWND;
auto set_window_target() -> void;
auto setup_window() -> void;
HRESULT directx_init();
void CreateRenderTarget();
void CleanupRenderTarget();
WPARAM render_loop();