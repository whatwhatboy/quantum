#include <d3d11.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#pragma comment(lib, "d3d11.lib")

namespace Process {
	inline DWORD ID;
	inline HANDLE Handle;
	inline HWND Hwnd;
	inline HMODULE Module;
	inline WNDPROC WndProc;
	inline int WindowWidth;
	inline int WindowHeight;
	inline LPCSTR Title;
	inline LPCSTR ClassName;
	inline LPCSTR Path;
}

class EditorColorScheme
{
    // 0xRRGGBBAA
    inline static int BackGroundColor = 0x25213100;
    inline static int TextColor = 0xF4F1DE00;
    inline static int MainColor = 0xDA115E00;
    inline static int MainAccentColor = 0xFFB6C100;
    inline static int HighlightColor = 0xFF69B400;

    inline static int Black = 0x00000000;
    inline static int White = 0xFFFFFF00;

    inline static int AlphaTransparent = 0x00;
    inline static int Alpha20 = 0x33;
    inline static int Alpha40 = 0x66;
    inline static int Alpha50 = 0x80;
    inline static int Alpha60 = 0x99;
    inline static int Alpha80 = 0xCC;
    inline static int Alpha90 = 0xE6;
    inline static int AlphaFull = 0xFF;

    static float GetR(int colorCode) { return (float)((colorCode & 0xFF000000) >> 24) / (float)(0xFF); }
    static float GetG(int colorCode) { return (float)((colorCode & 0x00FF0000) >> 16) / (float)(0xFF); }
    static float GetB(int colorCode) { return (float)((colorCode & 0x0000FF00) >> 8) / (float)(0xFF); }
    static float GetA(int alphaCode) { return ((float)alphaCode / (float)0xFF); }

    static ImVec4 GetColor(int c, int a = Alpha80) { return ImVec4(GetR(c), GetG(c), GetB(c), GetA(a)); }
    static ImVec4 Darken(ImVec4 c, float p) { return ImVec4(fmax(0.f, c.x - 1.0f * p), fmax(0.f, c.y - 1.0f * p), fmax(0.f, c.z - 1.0f * p), c.w); }
    static ImVec4 Lighten(ImVec4 c, float p) { return ImVec4(fmax(0.f, c.x + 1.0f * p), fmax(0.f, c.y + 1.0f * p), fmax(0.f, c.z + 1.0f * p), c.w); }

    static ImVec4 Disabled(ImVec4 c) { return Darken(c, 0.6f); }
    static ImVec4 Hovered(ImVec4 c) { return Lighten(c, 0.2f); }
    static ImVec4 Active(ImVec4 c) { return Lighten(ImVec4(c.x, c.y, c.z, 1.0f), 0.1f); }
    static ImVec4 Collapsed(ImVec4 c) { return Darken(c, 0.2f); }

public:

    static void SetColors(int backGroundColor, int textColor, int mainColor, int mainAccentColor, int highlightColor)
    {
        BackGroundColor = backGroundColor;
        TextColor = textColor;
        MainColor = mainColor;
        MainAccentColor = mainAccentColor;
        HighlightColor = highlightColor;
    }

    static void ApplyTheme()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_Text] = GetColor(TextColor);
        colors[ImGuiCol_TextDisabled] = Disabled(colors[ImGuiCol_Text]);
        colors[ImGuiCol_WindowBg] = GetColor(BackGroundColor);
        colors[ImGuiCol_ChildBg] = GetColor(Black, Alpha20);
        colors[ImGuiCol_PopupBg] = GetColor(BackGroundColor, Alpha90);
        colors[ImGuiCol_Border] = Lighten(GetColor(BackGroundColor), 0.4f);
        colors[ImGuiCol_BorderShadow] = GetColor(Black);
        colors[ImGuiCol_FrameBg] = GetColor(MainAccentColor, Alpha40);
        colors[ImGuiCol_FrameBgHovered] = Hovered(colors[ImGuiCol_FrameBg]);
        colors[ImGuiCol_FrameBgActive] = Active(colors[ImGuiCol_FrameBg]);
        colors[ImGuiCol_TitleBg] = GetColor(BackGroundColor, Alpha80);
        colors[ImGuiCol_TitleBgActive] = Active(colors[ImGuiCol_TitleBg]);
        colors[ImGuiCol_TitleBgCollapsed] = Collapsed(colors[ImGuiCol_TitleBg]);
        colors[ImGuiCol_MenuBarBg] = Darken(GetColor(BackGroundColor), 0.2f);
        colors[ImGuiCol_ScrollbarBg] = Lighten(GetColor(BackGroundColor, Alpha50), 0.4f);
        colors[ImGuiCol_ScrollbarGrab] = Lighten(GetColor(BackGroundColor), 0.3f);
        colors[ImGuiCol_ScrollbarGrabHovered] = Hovered(colors[ImGuiCol_ScrollbarGrab]);
        colors[ImGuiCol_ScrollbarGrabActive] = Active(colors[ImGuiCol_ScrollbarGrab]);
        colors[ImGuiCol_CheckMark] = GetColor(HighlightColor);
        colors[ImGuiCol_SliderGrab] = GetColor(HighlightColor);
        colors[ImGuiCol_SliderGrabActive] = Active(colors[ImGuiCol_SliderGrab]);
        colors[ImGuiCol_Button] = GetColor(MainColor, Alpha80);
        colors[ImGuiCol_ButtonHovered] = Hovered(colors[ImGuiCol_Button]);
        colors[ImGuiCol_ButtonActive] = Active(colors[ImGuiCol_Button]);
        colors[ImGuiCol_Header] = GetColor(MainAccentColor, Alpha80);
        colors[ImGuiCol_HeaderHovered] = Hovered(colors[ImGuiCol_Header]);
        colors[ImGuiCol_HeaderActive] = Active(colors[ImGuiCol_Header]);
        colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
        colors[ImGuiCol_SeparatorHovered] = Hovered(colors[ImGuiCol_Separator]);
        colors[ImGuiCol_SeparatorActive] = Active(colors[ImGuiCol_Separator]);
        colors[ImGuiCol_ResizeGrip] = GetColor(MainColor, Alpha20);
        colors[ImGuiCol_ResizeGripHovered] = Hovered(colors[ImGuiCol_ResizeGrip]);
        colors[ImGuiCol_ResizeGripActive] = Active(colors[ImGuiCol_ResizeGrip]);
        colors[ImGuiCol_Tab] = GetColor(MainColor, Alpha60);
        colors[ImGuiCol_TabHovered] = Hovered(colors[ImGuiCol_Tab]);
        colors[ImGuiCol_TabActive] = Active(colors[ImGuiCol_Tab]);
        colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
        colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive];
        colors[ImGuiCol_PlotLines] = GetColor(HighlightColor);
        colors[ImGuiCol_PlotLinesHovered] = Hovered(colors[ImGuiCol_PlotLines]);
        colors[ImGuiCol_PlotHistogram] = GetColor(HighlightColor);
        colors[ImGuiCol_PlotHistogramHovered] = Hovered(colors[ImGuiCol_PlotHistogram]);
        colors[ImGuiCol_TextSelectedBg] = GetColor(HighlightColor, Alpha40);
        colors[ImGuiCol_DragDropTarget] = GetColor(HighlightColor, Alpha80);;
        colors[ImGuiCol_NavHighlight] = GetColor(White);
        colors[ImGuiCol_NavWindowingHighlight] = GetColor(White, Alpha80);
        colors[ImGuiCol_NavWindowingDimBg] = GetColor(White, Alpha20);
        colors[ImGuiCol_ModalWindowDimBg] = GetColor(Black, Alpha60);

        ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_Right;
    }
};

typedef HRESULT(APIENTRY* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
inline IDXGISwapChainPresent oIDXGISwapChainPresent;

typedef void(APIENTRY* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
inline ID3D11DrawIndexed oID3D11DrawIndexed;

extern void ImplHookDX11_Init(HMODULE hModule);

extern void ImplHookDX11_Uninit();

//D3D11 Methods Table:
//[0] QueryInterface
//[1] AddRef
//[2] Release
//[3] SetPrivateData
//[4] SetPrivateDataInterface
//[5] GetPrivateData
//[6] GetParent
//[7] GetDevice
//[8] Present
//[9] GetBuffer
//[10] SetFullscreenState
//[11] GetFullscreenState
//[12] GetDesc
//[13] ResizeBuffers
//[14] ResizeTarget
//[15] GetContainingOutput
//[16] GetFrameStatistics
//[17] GetLastPresentCount
//[18] QueryInterface
//[19] AddRef
//[20] Release
//[21] CreateBuffer
//[22] CreateTexture1D
//[23] CreateTexture2D
//[24] CreateTexture3D
//[25] CreateShaderResourceView
//[26] CreateUnorderedAccessView
//[27] CreateRenderTargetView
//[28] CreateDepthStencilView
//[29] CreateInputLayout
//[30] CreateVertexShader
//[31] CreateGeometryShader
//[32] CreateGeometryShaderWithStreamOutput
//[33] CreatePixelShader
//[34] CreateHullShader
//[35] CreateDomainShader
//[36] CreateComputeShader
//[37] CreateClassLinkage
//[38] CreateBlendState
//[39] CreateDepthStencilState
//[40] CreateRasterizerState
//[41] CreateSamplerState
//[42] CreateQuery
//[43] CreatePredicate
//[44] CreateCounter
//[45] CreateDeferredContext
//[46] OpenSharedResource
//[47] CheckFormatSupport
//[48] CheckMultisampleQualityLevels
//[49] CheckCounterInfo
//[50] CheckCounter
//[51] CheckFeatureSupport
//[52] GetPrivateData
//[53] SetPrivateData
//[54] SetPrivateDataInterface
//[55] GetFeatureLevel
//[56] GetCreationFlags
//[57] GetDeviceRemovedReason
//[58] GetImmediateContext
//[59] SetExceptionMode
//[60] GetExceptionMode
//[61] QueryInterface
//[62] AddRef
//[63] Release
//[64] GetDevice
//[65] GetPrivateData
//[66] SetPrivateData
//[67] SetPrivateDataInterface
//[68] SetConstantBuffers
//[69] SetShaderResources
//[70] SetShader
//[71] SetSamplers
//[72] SetShader
//[73] DrawIndexed
//[74] Draw
//[75] Map
//[76] Unmap
//[77] SetConstantBuffers
//[78] IASetInputLayout
//[79] IASetVertexBuffers
//[80] IASetIndexBuffer
//[81] DrawIndexedInstanced
//[82] DrawInstanced
//[83] SetConstantBuffers
//[84] SetShader
//[85] IASetPrimitiveTopology
//[86] SetShaderResources
//[87] SetSamplers
//[88] Begin
//[89] End
//[90] GetData
//[91] SetPredication
//[92] SetShaderResources
//[93] SetSamplers
//[94] OMSetRenderTargets
//[95] OMSetRenderTargetsAndUnorderedAccessViews
//[96] OMSetBlendState
//[97] OMSetDepthStencilState
//[98] SOSetTargets
//[99] DrawAuto
//[100] DrawIndexedInstancedIndirect
//[101] DrawInstancedIndirect
//[102] Dispatch
//[103] DispatchIndirect
//[104] RSSetState
//[105] RSSetViewports
//[106] RSSetScissorRects
//[107] CopySubresourceRegion
//[108] CopyResource
//[109] UpdateSubresource
//[110] CopyStructureCount
//[111] ClearRenderTargetView
//[112] ClearUnorderedAccessViewUint
//[113] ClearUnorderedAccessViewFloat
//[114] ClearDepthStencilView
//[115] GenerateMips
//[116] SetResourceMinLOD
//[117] GetResourceMinLOD
//[118] ResolveSubresource
//[119] ExecuteCommandList
//[120] SetShaderResources
//[121] SetShader
//[122] SetSamplers
//[123] SetConstantBuffers
//[124] SetShaderResources
//[125] SetShader
//[126] SetSamplers
//[127] SetConstantBuffers
//[128] SetShaderResources
//[129] CSSetUnorderedAccessViews
//[130] SetShader
//[131] SetSamplers
//[132] SetConstantBuffers
//[133] VSGetConstantBuffers
//[134] PSGetShaderResources
//[135] PSGetShader
//[136] PSGetSamplers
//[137] VSGetShader
//[138] PSGetConstantBuffers
//[139] IAGetInputLayout
//[140] IAGetVertexBuffers
//[141] IAGetIndexBuffer
//[142] GSGetConstantBuffers
//[143] GSGetShader
//[144] IAGetPrimitiveTopology
//[145] VSGetShaderResources
//[146] VSGetSamplers
//[147] GetPredication
//[148] GSGetShaderResources
//[149] GSGetSamplers
//[150] OMGetRenderTargets
//[151] OMGetRenderTargetsAndUnorderedAccessViews
//[152] OMGetBlendState
//[153] OMGetDepthStencilState
//[154] SOGetTargets
//[155] RSGetState
//[156] RSGetViewports
//[157] RSGetScissorRects
//[158] HSGetShaderResources
//[159] HSGetShader
//[160] HSGetSamplers
//[161] HSGetConstantBuffers
//[162] DSGetShaderResources
//[163] DSGetShader
//[164] DSGetSamplers
//[165] DSGetConstantBuffers
//[166] CSGetShaderResources
//[167] CSGetUnorderedAccessViews
//[168] CSGetShader
//[169] CSGetSamplers
//[170] CSGetConstantBuffers
//[171] ClearState
//[172] Flush
//[173] GetType
//[174] GetContextFlags
//[175] FinishCommandList
//[176] CopySubresourceRegion1
//[177] UpdateSubresource1
//[178] DiscardResource
//[179] DiscardView
//[180] SetConstantBuffers1
//[181] SetConstantBuffers1
//[182] SetConstantBuffers1
//[183] SetConstantBuffers1
//[184] SetConstantBuffers1
//[185] SetConstantBuffers1
//[186] VSGetConstantBuffers1
//[187] HSGetConstantBuffers1
//[188] DSGetConstantBuffers1
//[189] GSGetConstantBuffers1
//[190] PSGetConstantBuffers1
//[191] CSGetConstantBuffers1
//[192] SwapDeviceContextState
//[193] ClearView
//[194] DiscardView1
//[195] UpdateTileMappings
//[196] CopyTileMappings
//[197] CopyTiles
//[198] UpdateTiles
//[199] ResizeTilePool
//[200] TiledResourceBarrier
//[201] IsAnnotationEnabled
//[202] SetMarkerInt
//[203] BeginEventInt
//[204] EndEvent