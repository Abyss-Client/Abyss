// class by sleepyfish for abyss recode
// February 2024 Tuesday 3:03 AM

#ifndef NEWABYSS_CLICKGUIUTILS_H
#define NEWABYSS_CLICKGUIUTILS_H

#include "../gui/ClickGui.h"

#include "../../../../../libraries/imgui/imgui.h"
#include "../../../../../assets/fonts/quicksand.h"
#include "../../../../../assets/fonts/quicksandMedium.h"
#include "../../../../../assets/fonts/quicksandBold.h"

class ClickGuiUtils {

public:

    static void applyFonts() {
        const ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontDefault();

        ClickGui::fontSmaller       = io.Fonts->AddFontFromMemoryTTF(quicksand, 78948, 15.0f); // 14
        ClickGui::fontDefault       = io.Fonts->AddFontFromMemoryTTF(quicksand, 78948, 16.0f); // 16
        ClickGui::fontDefaultBigger = io.Fonts->AddFontFromMemoryTTF(quicksand, 78948, 18.0f); // 18
        ClickGui::fontMedium        = io.Fonts->AddFontFromMemoryTTF(quicksandMedium, 78820, 24.0f); // 24
        ClickGui::fontBold          = io.Fonts->AddFontFromMemoryTTF(quicksandBold, 78596, 24.0f);   // 24

        // io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ebrima.ttf") is also good
    }

    static void applyDefaultTheme() {
        ImVec4* colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.045f, 0.045f, 0.045f, 0.90f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.045f, 0.045f, 0.045f, 0.90f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.045f, 0.045f, 0.045f, 0.90f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.045f, 0.045f, 0.045f, 0.90f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.065f, 0.065f, 0.065f, 0.90f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.065f, 0.065f, 0.065f, 0.90f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.065f, 0.065f, 0.065f, 0.90f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.0f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.4f, 0.7f, 0.7f, 1.0f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5, 0.89f, 0.89f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.19f, 0.19f, 0.19f, 1.0f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.44f, 0.44f, 0.67f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
        colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 0.3f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
        colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
        colors[ImGuiCol_TabHovered] = ImVec4(0, 0.23f, 0.23f, 0.67f);
        colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.0f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.0f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.0f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    static void applyPurpleTheme() {
        ImVec4* colors = ImGui::GetStyle().Colors;

        const ImVec4 backGround = ImVec4(0x0C / 255.0f, 0x0C / 255.0f, 0x0C / 255.0f, 1.0f);
        const ImVec4 backGroundBrighter = ImVec4(0x1E / 255.0f, 0x1E / 255.0f, 0x1E / 255.0f, 1.0f);
        const ImVec4 lineColorPurple = ImVec4(220.0f / 255.0f, 64.0f / 255.0f, 255.0f / 255.0f, 1.00f);

        colors[ImGuiCol_CheckMark] = lineColorPurple;
        colors[ImGuiCol_SliderGrab] = lineColorPurple;
        colors[ImGuiCol_SliderGrabActive] = lineColorPurple;

        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_Separator] = lineColorPurple;

        colors[ImGuiCol_WindowBg] = backGround;
        colors[ImGuiCol_ChildBg] = backGroundBrighter;

        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_FrameBg] = ImVec4(29 / 255.0f, 29 / 255.0f, 29 / 255.0f, 1.0f);
        colors[ImGuiCol_TitleBg] = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.0f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.0f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.0f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);

        colors[ImGuiCol_Border] = ImVec4(120 / 255.0f, 5 / 255.0f, 170 / 255.0f, 1.0f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.25f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(33 / 255.0f, 35 / 255.0f, 47 / 255.0f, 1.0f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.0f);
        colors[ImGuiCol_ButtonActive] = ImVec4(135 / 255.0f, 135 / 255.0f, 135 / 255.0f, 1.0f);
        colors[ImGuiCol_Header] = ImVec4(255 / 255.0f, 200 / 255.0f, 0 / 255.0f, 1.0f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.0f);
        colors[ImGuiCol_HeaderActive] = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.0f);
        colors[ImGuiCol_Separator] = ImVec4(0, 0, 0, 1);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0, 0, 0, 1);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0, 0, 0, 1);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.0f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.0f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

        ImGuiStyle& style = ImGui::GetStyle();

        style.Alpha = 1.0f;
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        style.WindowMinSize = ImVec2(32.0f, 32.0f);
        style.WindowRounding = 8.0f;
        style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
        style.ChildRounding = 4.0f;
        style.FramePadding = ImVec2(4.0f, 3.0f);
        style.FrameRounding = 4.0f;
        style.ItemSpacing = ImVec2(8.0f, 8.0f);
        style.ItemInnerSpacing = ImVec2(8.0f, 8.0f);
        style.TouchExtraPadding = ImVec2(0.0f, 0.0f);
        style.IndentSpacing = 20.0f;
        style.ColumnsMinSpacing = 0.0f;
        style.ScrollbarSize = 6.0f;
        style.ScrollbarRounding = 3.0f;
        style.GrabMinSize = 5.0f;
        style.GrabRounding = 3.0f;
        style.ButtonTextAlign = ImVec2(0.0f, 0.5f);
        style.DisplayWindowPadding = ImVec2(22.0f, 22.0f);
        style.DisplaySafeAreaPadding = ImVec2(20.0f, 20.0f);
        style.AntiAliasedLines = true;
        style.CurveTessellationTol = 3.0f;
    }
};

#endif //NEWABYSS_CLICKGUIUTILS_H