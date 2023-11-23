#pragma once
#include <locale>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <Wincrypt.h>
#include <winternl.h>
#include <stdint.h>
#include <cstdint>
#include <stdio.h>
#include <cmath>
#include <array>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iomanip>
#include <functional>
#include <shlobj_core.h>
#include <intrin.h>
#include <MinHook.h>
#include <wrl/client.h>
#include <minwindef.h>
#include "obfuscator.h"
#include "rage/fwddec.hpp"
#include "rage/Base.hpp"
#include "Invoker.hpp"
#include "rage/Enums.hpp"
#include <cstdarg>
#include <d3d11.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define IS_DEBUG_VERSION

#pragma warning(disable: 4477)
#pragma warning(disable: 4313)
#pragma warning(disable: 4081)
#pragma warning(disable: 4838)

#pragma intrinsic(_ReturnAddress)

#define MENU_BUILD_DATE __DATE__
#define MENU_BUILD_TIME __TIME__

#pragma message("========== Building Quantum ==========")
#pragma message("Date -> " MENU_BUILD_DATE)
#pragma message("Time -> " MENU_BUILD_TIME)
#pragma message("======================================")

#define WORKING_DUMP_BASE 0x7FF62CBA0000

inline std::uintptr_t GTA_JMP_RBX = 0x7FF62DCC6970; // 23 C3 C1 E0 0C  (-1)
inline std::uintptr_t GTA_NATIVE_REGISTRATION = 0x7FF62F8DFBF0; // 48 8D 0D ? ? ? ? 48 8B 14 FA
inline std::uintptr_t GTA_GET_NATIVE_HANDLER = 0x7FF62D5D8934; // 48 8D 0D ? ? ? ? 48 8B 14 FA (First call)
inline std::uintptr_t GTA_RETURN_FALSE_SUB = 0x7FF6324E68EF; // 32 C0 C3 (Any)
inline std::uintptr_t GTA_SET_VECTOR_RESULTS = 0x7FF62E11D60C; // 83 79 18 00 48 8B D1 74 4A 
inline std::uintptr_t GTA_GET_SESSION_HOST_NET_GAME_PLAYER = 0x7FF62DBCFE98; // 40 53 48 83 EC 20 48 8B 49 20 48 8D 54 24 ? (Go back until you find call near ptr)
inline std::uintptr_t GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX = 0x7FF62E1CB98C; // 80 F9 20 73 13 
inline std::uintptr_t GTA_GET_SCRIPT_INDEX_FROM_ENTITY = 0x7FF62E124DE8; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB
inline std::uintptr_t GTA_GET_ENTITY_FROM_SCRIPT_GUID = 0x7FF62D5A8F68; // 40 53 48 83 EC 20 48 63 DA E8 ? ? ? ? 48 85 C0 74 21 (First call you see)
inline std::uintptr_t GTA_GET_NET_OBJECT_BY_NET_ID = 0x7FF62DBD1C44; // 48 89 5C 24 ? 48 89 6C 24 ? 66 89 54 24 ? (Find jmp xref with 1 xref from caller)
inline std::uintptr_t GTA_GET_LOCAL_PLAYER_PED = 0x7FF62D226E54; // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
inline std::uintptr_t GTA_GET_SYNC_TREE_FROM_CLONE_TYPE = 0x7FF62DC8F128; // 0F B7 CA 83 F9 07 
inline std::uintptr_t GTA_STREAMED_SCRIPTS = 0x7FF62F174FA0; // 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 38 FF 74 2D 
inline std::uintptr_t GTA_LOCAL_SCRIPT_HANDLERS = 0x7FF62F14ADB0; // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
inline std::uintptr_t GTA_NETWORKED_SCRIPT_HANDLERS = 0x7FF62F14BB50; // // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
inline std::uintptr_t GTA_REMOVE_PLAYER_FROM_PLAYER_MGR = 0x7FF62DCA6F74; // 48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 E8 ? ? ? ? 84 C0 75 14 
inline std::uintptr_t GTA_REGISTER_GAME_FILE = 0x7FF62E1462A0; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 
inline std::uintptr_t GTA_CHANGE_NET_OBJ_OWNER = 0x7FF62E1C62D4; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 81 EC ? ? ? ? 44 8A 62 4B 
inline std::uintptr_t GTA_GET_VEHICLE_PAINT_LIST_ARRAY = 0x7FF62D199E24; // 4C 8B 0D ? ? ? ? 45 33 C0 4D 85 C9
inline std::uintptr_t GTA_PACK_CLONE_REMOVE = 0x7FF62E1D9730; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 80 78 ? ? 
inline std::uintptr_t GTA_PACK_CLONE_SYNC = 0x7FF62E1E0AAC; // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 02 
inline std::uintptr_t GTA_MODEL_INFO_LIST_POOL = 0x7FF62E993BB0; // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 (Last add instr with addr)
inline std::uintptr_t GTA_WATER_TUNE_XML = 0x7FF62E83FBF4; // F3 0F 11 05 ? ? ? ? F3 0F 10 05 ? ? ? ? F3 0F 11 0D ? ? ? ? 0F 28 0D ? ? ? ? 
inline std::uintptr_t GTA_WATER_QUAD_XML = 0x7FF62EDB4170; // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ? 
inline std::uintptr_t GTA_WATER_QUAD_XML_COUNT = 0x7FF62EDB4178; // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ?  (+ 0x8)
inline std::uintptr_t GTA_HUD_COLOUR_POOL = 0x7FF62EAE0690; // 41 8B 8C 84 ? ? ? ? 41 0F B6 C0 
inline std::uintptr_t GTA_PED_FACTORY = 0x7FF62F04CB48; // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
inline std::uintptr_t GTA_ATTACHMENT_EXTENSION_INST_POOL = 0x7FF62F9C06E8; // 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0E 48 8B D6 48 8B C8 E8 ? ? ? ? 48 8B D8 48 89 5F 48 
inline std::uintptr_t GTA_GAME_GLOBALS = 0x7FF62F8E0BD0; // 4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11 
inline std::uintptr_t GTA_SUPER_GRIP_FLOAT = 0x7FF62E4801A4; // F3 0F 59 15 ? ? ? ? F3 41 0F 58 D2 F3 0F 59 D0 
inline std::uintptr_t GTA_NETWORK_OBJECT_MGR_INTERFACE = 0x7FF62F43B450; // 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 01 FF 50 30 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 48 8B 88 ? ? ? ? (Any)
inline std::uintptr_t GTA_NETWORK_PLAYER_MGR_INTERFACE = 0x7FF62F9CA8E0; // 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? C3
inline std::uintptr_t GTA_FORCE_SCRIPT_HOST = 0x7FF62D5BD09C; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B FA 48 8B D9 E8 ? ? ? ? 83 7B 10 08 
inline std::uintptr_t GTA_SMALL_HOST_TOKEN_PATCH = 0x7FF62F89ECEB; // C6 05 ? ? ? ? ? 48 8B CB E8 ? ? ? ? 84 C0 75 08 
inline std::uintptr_t GTA_NETWORK_OBJECT_MGR_TABLE = 0x7FF62E598C88;
inline std::uintptr_t GTA_NET_OBJ_PED_NODE_DATA_ACCESSOR_TABLE = 0x7FF62E5A5FC8;
inline std::uintptr_t GTA_NET_OBJ_OBJECT_NODE_DATA_ACCESSOR_TABLE = 0x7FF62E5A22E8;
inline std::uintptr_t GTA_REMOVE_WEAPON_EVENT_TABLE = 0x7FF62E5ADB18;
inline std::uintptr_t GTA_REMOVE_ALL_WEAPONS_EVENT_TABLE = 0x7FF62E5ADBE8;
inline std::uintptr_t GTA_GAME_WEATHER_EVENT_TABLE = 0x7FF62E5AD8A8;
inline std::uintptr_t GTA_GAME_CLOCK_EVENT_TABLE = 0x7FF62E5AD7D8;
inline std::uintptr_t GTA_SCRIPTED_GAME_EVENT_TABLE = 0x7FF62E5AE738;
inline std::uintptr_t GTA_EXPLOSION_EVENT_TABLE = 0x7FF62E5ADE48;
inline std::uintptr_t GTA_FIRE_EVENT_TABLE = 0x7FF62E5ADD88;
inline std::uintptr_t GTA_INCREMENT_STAT_EVENT_TABLE = 0x7FF62E5B0458;
inline std::uintptr_t GTA_PED_INST_POOL = 0x7FF62F04C9B8; // In first vtable func
inline std::uintptr_t GTA_OBJ_INST_POOL = 0x7FF62F074310; // In first vtable func
inline std::uintptr_t GTA_VEH_LIST_POOL = 0x7FF62F3B8718; // In first vtable func
inline std::uintptr_t GTA_GET_CHAT_MSG_DATA = 0x7FF62DD231F8; // 48 8B C4 48 89 58 08 48 89 70 10 57 48 83 EC 20 48 8B F1 48 8D 48 18 33 DB 48 8B FA 89 58 18 E8 ? ? ? ? 85 C0 74 4C 8B 44 24 40 39 05 ? ? ? ? 75 40 41 B8 ? ? ? ? 
inline std::uintptr_t GTA_WRITE_SYNC_DATA_STRING = 0x7FF62DE54D4C; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 20 33 F6 4C 8B E2 
inline std::uintptr_t GTA_WRITE_SYNC_DATA_QWORD = 0x7FF62DE5501C; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20 
inline std::uintptr_t GTA_ASSIGN_PHYSICAL_INDEX = 0x7FF62E1DD2A8; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8 
inline std::uintptr_t GTA_WAYPOINT_PATH_DATA = 0x7FF62EAFA710; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 48 8D B9 ? ? ? ? 48 8B D9 45 33 F6 48 8B 0F 41 8A E8 (Find 1 xref with ptr to wp data)

inline std::uintptr_t GTA_SEND_CLONE_SYNC_PATCH = 0x7FF62E1E0AAC; // netObjectMgrBase + 0xA8‬ 
inline std::uintptr_t GTA_BUILDING_INST_POOL = 0x7FF62F1108F8; // ptr in 1st vt fn
inline std::uintptr_t GTA_WRITE_SYNC_DATA_BOOL = 0x7FF62DE54B70; // 1st jumpout first static virtual in datawriter

inline std::uintptr_t GTA_GET_MODEL_INFO = 0x7FF62E1B6A38; // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 
inline std::uintptr_t GTA_PROCESS_NET_OBJ = 0x7FF62E1C5AC0; // 

inline std::uintptr_t GTA_PACK_CLONE_CREATE = 0x7FF62E1C6DB0; // 7FF7F9349D48

inline std::uintptr_t GTA_SEND_CLONE_SYNC = 0x7FF62E1DAF7C; //

#define TRANSLATE_RUNTIME_RVA(v) {\
    std::uint64_t cache = v;\
    std::uint64_t base = reinterpret_cast<std::uint64_t>(GetModuleHandle(NULL));\
    if (base != WORKING_DUMP_BASE){\
        v = (base + (v - WORKING_DUMP_BASE));\
        if (v == cache || v == base || v == NULL || v == WORKING_DUMP_BASE) {\
            Sleep(40000);\
            return false;\
        }\
    }\
}\

namespace KEYBOARD {

    inline bool IS_KEYBOARD_INPUT_JUST_PRESSED(std::int32_t key) {
        return GetAsyncKeyState(key) & 0x0001;
    }

    inline bool IS_KEYBOARD_INPUT_PRESSED(std::int32_t key) {
        return GetAsyncKeyState(key) & 0x8000;
    }
}

inline ImFont* m_font{};
inline HMODULE g_hmodule{};
inline HANDLE g_main_thread{};
inline DWORD g_main_thread_id{};
inline bool g_running{ true };

enum eGameState : std::uint32_t
{
    Playing = 0
};

namespace funcs {
    using DoesCamExist = bool(*)(Cam cam);
    using NativeHandler = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
    using FixVectors = void(*)(rage::scrNativeCallContext*);
    using FileRegister = uint32_t*(*)(int*, const char*, bool, const char*, bool);
	using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    using GetPlayerName = const char* (_fastcall*)(int32_t index);
    using GetNetPlayer = int64_t(_fastcall*)(int32_t index);
}
class pointers
{
public:
    funcs::DoesCamExist m_DCE{};
    funcs::FixVectors m_FV{};
    funcs::FileRegister m_FR{};
    funcs::NativeHandler m_GNH{};
	funcs::WndProc* m_WP{};
	funcs::GetPlayerName m_GPN{};
	funcs::GetNetPlayer m_GNP{};
    std::uint64_t* m_FC{};
    PVOID* m_MSB{};
    char* m_GB{};
    bool* m_ISS{};
    eGameState* m_GS{};
    rage::scrNativeRegistrationTable* m_NRT{};
    std::int64_t** m_SG{};
    HWND g_hWnd;
    bool g_testui = true;
    void g_wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (msg == WM_KEYUP && wParam == VK_MULTIPLY) {
            g_testui = !g_testui;
        }
        if (ImGui::GetCurrentContext()) ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
    }
    void g_ontick();
    ID3D11Device* m_d3d_device;
    ID3D11DeviceContext* m_d3d_device_context;
};

inline pointers ptr;

struct Hooks
{
    static bool DoesCamExist(Cam cam);
    static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static constexpr auto swapchain_num_funcs = 19;
    static constexpr auto swapchain_present_index = 8;
    static constexpr auto swapchain_resizebuffers_index = 13;
    static HRESULT swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
    static HRESULT swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);
};

class Hooking
{
    friend Hooks;
public:
    void* m_OriginalDoesCamExist{};
    void* m_OriginalWndProc{};
    void* m_OriginalPresentIndex{};
    void* m_OriginalPresentBuffersIndex{};
};

inline Hooking hook;

inline std::vector<std::function<void()>> Queue;

inline void printfnl(const char* msg, ...) {
    std::va_list args{};
    va_start(args, msg);
    printf("%s\n", msg);
    va_end(args);
}

inline void setup_imgui_style() {
	auto& style = ImGui::GetStyle();
	style.WindowPadding = { 10.f, 10.f };
	style.PopupRounding = 0.f;
	style.FramePadding = { 8.f, 4.f };
	style.ItemSpacing = { 10.f, 8.f };
	style.ItemInnerSpacing = { 6.f, 6.f };
	style.TouchExtraPadding = { 0.f, 0.f };
	style.IndentSpacing = 21.f;
	style.ScrollbarSize = 15.f;
	style.GrabMinSize = 8.f;
	style.WindowBorderSize = 1.f;
	style.ChildBorderSize = 0.f;
	style.PopupBorderSize = 1.f;
	style.FrameBorderSize = 3.5f;
	style.WindowRounding = 0.f;
	style.ChildRounding = 0.f;
	style.FrameRounding = 0.f;
	style.ScrollbarRounding = 0.f;
	style.GrabRounding = 0.f;
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.ButtonTextAlign = { 0.5f, 0.5f };
	style.DisplaySafeAreaPadding = { 3.f, 3.f };

	auto& colors = style.Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.50f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.41f, 0.41f, 0.41f, 0.74f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.78f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 0.87f);
	colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
	colors[ImGuiCol_Separator] = ImVec4(0.38f, 0.38f, 0.38f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.50f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.64f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
}

inline void InitColor2() {

    ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5, 0.5);
    ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5, 0.5);
    ImGui::GetStyle().WindowRounding = 5.5f;
    ImGui::GetStyle().ChildRounding = 0.1f;
    ImGui::GetStyle().FrameRounding = 0.1f;
    ImGui::GetStyle().GrabRounding = 0.1f;
    ImGui::GetStyle().PopupRounding = 5.5f;
    ImGui::GetStyle().ScrollbarRounding = 0.5f;
    ImGui::GetStyle().AntiAliasedLines = true;
    ImGui::GetStyle().AntiAliasedFill = true;
    ImGui::GetStyle().CurveTessellationTol = 0.1f;
    ImGui::GetStyle().FrameBorderSize = 1.5f;
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 255);
    colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImGui::ColorConvertU32ToFloat4(ImColor(57, 119, 188, 255));
    colors[ImGuiCol_BorderShadow] = ImColor(41, 41, 41, 255);
    colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20, 255);
    colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30, 255);
    colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
    colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_ScrollbarBg] = ImColor(255, 255, 255, 0);
    colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 255, 255, 0);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(255, 255, 255, 0);
    colors[ImGuiCol_ScrollbarGrabActive] = ImColor(255, 255, 255, 0);
    colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_Button] = ImColor(20, 20, 20, 255);
    colors[ImGuiCol_ButtonHovered] = ImColor(30, 30, 30, 255);
    colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30, 255);
    colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
    colors[ImGuiCol_Separator] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_SeparatorHovered] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_SeparatorActive] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_PlotLines] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 255);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
}