// class by sleepyfish for abyss recode
// February 2024 Friday 12:58 AM

#ifndef NEWABYSS_TEXTGUI_H
#define NEWABYSS_TEXTGUI_H

#include "../../Module.h"
#include "../../../../../../../libraries/imgui/imgui.h"
#include "../../../utils/type/Vector4.h"
#include "../../settings/impl/ColorSetting.h"
#include "../../settings/impl/ModeSetting.h"
#include "../../settings/impl/BoolSetting.h"
#include "../../settings/impl/TextSetting.h"
#include "../../../utils/ClientUtils.h"

class TextGui : public Module {

public:
    TextGui();

    void onEnableEvent() override;
    void onDisableEvent() override;
    void onRenderTick() override;
    void onGuiRenderTick() override;

    const std::vector<String> colorModes {
        "Single", "Chroma", "Fade"
    };

    ImVec4 color = ImVec4(0.55f, 0.39f, 0.78f, 1.0f);
    ImVec4 colorFade1 = ImVec4(0.78f,  0.0f, 0.78f, 1.0f);
    ImVec4 colorFade2 = ImVec4( 0.0f,  0.0f, 0.78f, 1.0f);

    ColorSetting* colorFade1S = new ColorSetting("Color 1", colorFade1, false);
    ColorSetting* colorFade2S = new ColorSetting("  Fade Colors", colorFade2, true);
    BoolSetting* staticColor = new BoolSetting("Static Color", false);
    BoolSetting* useClientColor = new BoolSetting("Use Client Color", false);
    BoolSetting* invertAnimation = new BoolSetting("Invert Animation", false);
    // Space setting
    ModeSetting* colorMode = new ModeSetting("Mode", colorModes, "Fade");
    BoolSetting* renderName = new BoolSetting("Render Client name", true);
    BoolSetting* sortWidth = new BoolSetting("Sort Text Width", true);
    // Space setting
    TextSetting* customText = new TextSetting("Custom Text", ClientUtils::getNameWithVersion());
    BoolSetting* removeVisual = new BoolSetting("Remove Visual Modules", false);
    BoolSetting* rectangles = new BoolSetting("Render Background", true);
    BoolSetting* rounded = new BoolSetting("Rounded Background", true);
    BoolSetting* darkerBackground = new BoolSetting("Darker Background", false);

    static bool compareModuleByNameWidth(Module *a, Module *b);
};

#endif //NEWABYSS_TEXTGUI_H