#pragma once

/* KEY */
#include "../RELEASE_KERNEL/key.h"

/* WinNT */
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <winternl.h>
#include <stdio.h>
#include <string>
#include <TlHelp32.h>
#include <iomanip>
#include <random>
#include <chrono>

/* PREREST */
#include "utils/utils.h"
#include "driver/backend/driver_utils.h"
#include "driver/backend/xor.h"

/* CORE0 */
#include "driver/gD/Bypass.h"
#include "driver/backend/ia32.h"
#include "driver/uex/uex.h"

/* IMGUI */
#include "Lib/imgui/imgui.h"
#include "Lib/imgui/imgui_impl_dx11.h"
#include "Lib/imgui/imgui_impl_win32.h"

/* D3D11 */
#include <d2d1.h>
#include <d3d9types.h>
#include <d3d11.h>
#include "Lib/imgui/imgui.h"
#include "Lib/imgui/imgui_impl_dx11.h"
#include "Lib/imgui/imgui_impl_win32.h"
#include "Lib/imgui/imgui_internal.h"

/* OVERLAY */
#include "overlay/overlay.h"
#include "client/draw.h"