#pragma once

#define NOMINMAX

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // !IMGUI_DEFINE_MATH_OPERATORS

#include <cstddef>

#include <iostream>
#include <windows.h>

#include <memory>
#include <thread>

#include <mutex>
#include <shared_mutex>

#include <chrono>
namespace ch = std::chrono;

#include <string>
#include <random>

#include <filesystem>
namespace fs = std::filesystem;

#include <typeindex>
#include <expected>

#include <tlhelp32.h>
#include <dwmapi.h>

#include <corecrt_math_defines.h>

using u64 = std::uint64_t;
using i64 = std::int64_t;

using u32 = std::uint32_t;
using i32 = std::int32_t;

using u8 = std::uint8_t;
using i8 = std::int8_t;

using u16 = std::uint16_t;

typedef _Return_type_success_( return >= 0 ) LONG NTSTATUS;
#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)    // ntsubauth

#define TEST_BIT(value, bit) (((value) & (1 << (bit))) != 0)

// json

#include <nlohmann/json.hpp>

// vcruntimes

#include <impl/vcruntimes/hexrays.hpp>
#include <impl/vcruntimes/hash.hpp>
#include <impl/vcruntimes/constant.hpp>
#include <impl/vcruntimes/lazy_import.hpp>

// cryptopp

#include <cryptopp/rsa.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/pwdbased.h>  
#include <cryptopp/hex.h>

// web-requests

#include <cpr/cpr.h>

// zydis-memory

#include <Zydis/Zydis.h>
#include <dependencies/zydis/zydis.hpp>

// d3d11-runtimes

#include <d3d11.h>
#include <d3dx11.h>

// imgui-dependencies

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

// imgui-implimentation

#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_freetype.h>

// ime-window

#include <ime/ime.hpp>

// resources

#include <dependencies/binaries/bobi.hpp>
#include <dependencies/binaries/fonts.hpp>
#include <dependencies/binaries/unicodes.hpp>

// sdk-enums

#include <workspace/facepunch/core/enums/enums.hpp>

// globa-variables

#include <impl/vars/color/color.hpp>

#include <impl/vars/option/option.hpp>
using namespace option_interface;

#include <impl/vars/vars.hpp>

// utilities

#include <workspace/backend/elements/logging/logging.hpp>
#include <workspace/backend/elements/utility/utility.hpp>

// awaken-bypass

#include <dependencies/awaken/ia32.h>
#include <dependencies/awaken/control.h>
#include <dependencies/awaken/driver.hxx>

// melon-auto-updating-api

#include <workspace/backend/internal/cryptopp/cryptopp.hpp>

// monoauth-api

#include <workspace/backend/internal/monoauth/monoauth.hpp>
using namespace monoauth_interface;

// facepunc-unity-sdk

#include <workspace/facepunch/core/math/vector.hpp>
#include <workspace/facepunch/sdk.hpp>
#include <workspace/facepunch/core/structs/objects.hpp>

// drawing-sdk

#include <workspace/drawing/textures/textures.hpp>
#include <workspace/drawing/sprites/sprites.hpp>

#include <workspace/drawing/framework/framework.hpp>
using namespace framework_interface;

#include <workspace/drawing/fonts/fonts.hpp>

// cheat-loops

#include <impl/game/players/players.hpp>

// cheat-visuals

#include <impl/visuals/visuals.hpp>

// cheat-enviroment

#include <impl/game/env/env.hpp>

// menu widgets

#include <workspace/drawing/menu/styles/style_manager.hpp>
#include <workspace/drawing/menu/language/language_manager.hpp>
#include <workspace/drawing/menu/animations/animations.hpp>
#include <workspace/drawing/menu/help/help_manager.hpp>
#include <workspace/drawing/menu/pop ups/popup_manager.hpp>
#include <workspace/drawing/menu/tooltips/tooltip_manager.hpp>
#include <workspace/drawing/menu/tabs/tabs_manager.hpp>
#include <workspace/drawing/menu/search/search_manager.hpp>
#include <workspace/drawing/menu/colors/color_picker.hpp>
#include <workspace/drawing/menu/widgets/widgets_manager.hpp>
#include <workspace/drawing/menu/components/component_builder.hpp>
#include <workspace/drawing/menu/childs/child_manager.hpp>

// in-render menu

#include <impl/menu/menu.hpp>

// internal-render

#include <impl/render/render.hpp>