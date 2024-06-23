// class by sleepyfish for abyss recode
// February 2024 Tuesday 12:56 AM

#ifndef NEWABYSS_CLICKGUI_H
#define NEWABYSS_CLICKGUI_H

#include <windows.h>
#include "../../../../../libraries/imgui/imgui.h"
#include "../utils/type/String.h"

typedef void(*callback)();
typedef bool(*callback2)();

struct ClickGui {

    static void inject();
    static void unInject();
    static inline bool isNull = true;
    static inline bool draw = false;

    static inline float guiAlpha = 0.0f; // Initial alpha value
    static inline bool isFadingIn = false;
    static inline bool isFadingOut = false;

    static inline String guiTitle;
    static inline bool isGuiOpen;
    static inline bool fixedAlpha;
    static inline int guiKeybind;

    static inline ImFont* fontSmaller;
    static inline ImFont* fontDefault;
    static inline ImFont* fontDefaultBigger;
    static inline ImFont* fontMedium;
    static inline ImFont* fontBold;

    static void renderGui();
    static void renderShadow(ImVec2 posMin, ImVec2 posMax);

    static inline int categoryFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing;
    static inline int categoryPadding = 15;

    static inline HWND handleWindow;
    static inline HDC handleDeviceContext;

    static inline HGLRC originalGLContext;
    static inline HGLRC menuGLContext;

    static inline ImGuiContext* imGuiContext;

    static inline ImVec2 legitCatPos;
    static inline ImVec2 legitCatPosMax;

    static inline ImVec2 visualCatPos;
    static inline ImVec2 visualCatPosMax;

    static inline ImVec2 blatantCatPos;
    static inline ImVec2 blatantCatPosMax;

    static inline ImVec2 otherCatPos;
    static inline ImVec2 otherCatPosMax;

    static inline ImVec2 uselessCatPos;
    static inline ImVec2 uselessCatPosMax;

    static inline ImVec2 hudCatPos;
    static inline ImVec2 hudCatPosMax;

    static inline ImVec2 clientCatPos;
    static inline ImVec2 clientCatPosMax;

    static void onMenuOpen();

    static void hook_RenderSwapBuffers();
    static void unhook_RenderSwapBuffers();

    static void hook_onKey();
    static void unhook_onKey();

    static void hook_Packets();
    static void unhook_Packets();

    static void hook_onRender();
    static void unhook_onRender();

    static void hook_doRenderEntity();
    static void unhook_doRenderEntity();

    static void setupImgui();

};

#endif //NEWABYSS_CLICKGUI_H