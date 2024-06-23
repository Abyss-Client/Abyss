// class by sleepyfish for abyss recode
// February 2024 Friday 12:58 AM

#include <algorithm>
#include "TextGui.h"
#include "../../../gui/ClickGui.h"
#include "../../settings/impl/SpaceSetting.h"
#include "../../../client/Abyss.h"

std::vector<Module*> modules;

TextGui::TextGui() : Module("Text Gui", Category::Visual, "Render a list of enabled Modules") {
    this->addSetting(TextGui::colorMode);
    this->addSetting(TextGui::staticColor);
    this->addSetting(TextGui::useClientColor);
    this->addSetting(TextGui::colorFade1S);
    this->addSetting(TextGui::colorFade2S);
    this->addSetting(new SpaceSetting());
    this->addSetting(TextGui::invertAnimation);
    this->addSetting(new SpaceSetting());
    this->addSetting(TextGui::renderName);
    this->addSetting(TextGui::customText);
    this->addSetting(TextGui::sortWidth);
    this->addSetting(new SpaceSetting());
    this->addSetting(TextGui::removeVisual);
    this->addSetting(TextGui::rectangles);
    this->addSetting(TextGui::rounded);
    this->addSetting(TextGui::darkerBackground);
}

void TextGui::onEnableEvent() {
}

void TextGui::onDisableEvent() {
}

void TextGui::onGuiRenderTick() {
    if (TextGui::sortWidth->isEnabled()) {
        modules = Abyss::modManager.getModules().getVector();
        std::sort(modules.begin(), modules.end(), TextGui::compareModuleByNameWidth);
    } else {
        if (modules != Abyss::modManager.getModules().getVector())
            modules = Abyss::modManager.getModules().getVector();
    }
}

bool TextGui::compareModuleByNameWidth(Module* a, Module* b) {
    const float modAWidth = ClickGui::fontDefault->CalcTextSizeA(20.0f, 400.0f, 0.0f, a->getName().toChar()).x;
    const float modBWidth = ClickGui::fontDefault->CalcTextSizeA(20.0f, 400.0f, 0.0f, b->getName().toChar()).x;
    return modAWidth > modBWidth;
}

void TextGui::onRenderTick() {

    ImGui::Begin("Text Gui", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(40.0f, 8.0f));

    const ImColor32 secRectColor = ImGui::GetImColor32(ImGuiCol_Border, 2.1f);
    const ImColor rectColor = ImColor(0.0f, 0.0f, 0.0f, TextGui::darkerBackground->isEnabled() ? 0.65f : 0.35f);
    ImDrawList *list = ImGui::GetWindowDrawList();

    const float windowX = ImGui::GetWindowPos().x;
    const float windowY = ImGui::GetWindowPos().y;
    const float font_size = 20.0f;
    const float gui_rounding = TextGui::rounded->isEnabled() ? ClientUtils::gui_rounding : 0.0f;

    const float xx = windowX + 8.0f;

    if (TextGui::renderName->isEnabled()) {
        String gooberAhh = ClientUtils::getNameWithVersion();
        if (!TextGui::customText->text.equals(gooberAhh))
            gooberAhh = TextGui::customText->text;

        ImGui::Text("                                                  ");
        list->AddText(ClickGui::fontBold, font_size + 6.0f, ImVec2(xx, windowY), secRectColor, gooberAhh.toChar());
    }

    float moduleOffset = 0;
    float colorOffset = 0;
    for (Module *mod: modules) {
        if (!mod->isEnabled())
            continue;

        if (mod->hideModule)
            continue;

        if (TextGui::removeVisual->isEnabled())
            if (mod->getCategory() == Category::Visual)
                continue;

        if (TextGui::colorMode->getMode().equals("Single")) {
            if (TextGui::useClientColor->isEnabled()) {
                color = ImVec4(ClientUtils::clientColor[0], ClientUtils::clientColor[1], ClientUtils::clientColor[2], ClientUtils::clientColor[3]);
            } else {
                color = TextGui::colorFade1S->getColor();
            }
        }

        if (TextGui::colorMode->getMode().equals("Chroma")) {
            color = ColorUtils::getRainbow(ClientUtils::color_frequency / 100.0f, ClientUtils::color_brightness / 100.0f, ClientUtils::color_gamma / 100.0f, 255.0f, colorOffset);

            if (!TextGui::staticColor->isEnabled()) {
                if (TextGui::invertAnimation->isEnabled())
                    colorOffset++;
                else
                    colorOffset--;
            }
        }

        if (TextGui::colorMode->getMode().equals("Fade")) {
            if (TextGui::useClientColor->isEnabled()) {
                const ImVec4 normal = ImVec4(ClientUtils::clientColor[0], ClientUtils::clientColor[1], ClientUtils::clientColor[2], ClientUtils::clientColor[3]);
                const ImVec4 darker = ImVec4(normal.x * 0.4f, normal.y * 0.4f, normal.z * 0.4f, normal.w);

                color = ColorUtils::getGradient(normal, darker, 3.0f, colorOffset);
            } else {
                color = ColorUtils::getGradient(TextGui::colorFade1S->getColor(), TextGui::colorFade2S->getColor(), 3.0f, colorOffset);
            }

            if (!TextGui::staticColor->isEnabled()) {
                if (TextGui::invertAnimation->isEnabled())
                    colorOffset++;
                else
                    colorOffset--;
            }
        }

        if (rectangles->isEnabled()) {
            const float yy = windowY + moduleOffset + 40.0f;
            const float y1 = yy + 6.0f;
            const ImVec2 nig = ImVec2(xx, yy - (font_size / 2.0f) - 2.0f);
            const float vecLength = ClickGui::fontMedium->CalcTextSizeA(font_size, 400.0f, 0.0f, mod->getName().toChar()).x + windowX + 20.0f;

            list->AddRectFilled(nig, ImVec2(vecLength, y1), rectColor, gui_rounding);
            list->AddRectFilled(nig, ImVec2(windowX + 12.0f, y1), ImGui::GetImColor32(color));
        }

        list->AddText(ClickGui::fontMedium, font_size, ImVec2(windowX + 16.0f, windowY + moduleOffset + 26.0f), ImGui::GetImColor32(color), mod->getName().toChar());
        ImGui::Text("                                ");
        moduleOffset += 18.0f;
    }

    ImGui::PopStyleVar();
    ImGui::End();

}