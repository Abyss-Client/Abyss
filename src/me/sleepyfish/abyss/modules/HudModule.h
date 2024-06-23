// class by sleepyfish for abyss recode
#ifndef NEWABYSS_HUDMODULE_H
#define NEWABYSS_HUDMODULE_H

#include "Module.h"
#include "settings/impl/BoolSetting.h"
#include "../gui/ClickGui.h"
#include "../utils/ClientUtils.h"

class HudModule : public Module {

public:
    BoolSetting* background;
    BoolSetting* shadow;
    BoolSetting* brackets;
    BoolSetting* border;
    BoolSetting* rounded;

    String text;

    int width, height;

    bool autoSetPos = true;
    bool custom = false;

    // Constructor without keybind
    HudModule(const String n, const String d) : Module(n, Category::Hud, d),
        background(new BoolSetting("Background", false)),
        shadow(new BoolSetting("Shadow", false)),
        brackets(new BoolSetting("Brackets", false)),
        border(new BoolSetting("Border", false)),
        rounded(new BoolSetting("Rounded", false)
    ) {
        this->addSetting(background);
        this->addSetting(shadow);
        this->addSetting(brackets);
        this->addSetting(border);
        this->addSetting(rounded);
    }

    // Constructor with keybind
    HudModule(const String n, const String d, int k) : Module(n, Category::Hud, d, k),
        background(new BoolSetting("Background", false)),
        shadow(new BoolSetting("Shadow", false)),
        brackets(new BoolSetting("Brackets", false)),
        border(new BoolSetting("Border", false)),
        rounded(new BoolSetting("Rounded", false)
    ) {
        this->addSetting(background);
        this->addSetting(shadow);
        this->addSetting(brackets);
        this->addSetting(border);
        this->addSetting(rounded);
    }

    void onRenderTick() override {
        ImGui::SetNextWindowSize(ImVec2(this->width, this->height));
        ImGui::Begin((this->getName() + "Hud").toChar(), 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);

        if (this->custom) {
            this->renderMod();
            ImGui::End();
            return;
        }

        const ImVec2 size = ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
        const ImVec2 winPos = ImGui::GetWindowPos();

        this->renderMod();

        if (!this->text.equals("-")) {
            if (this->brackets->isEnabled())
                this->text = "[" + this->text.toString() + "]";

            const int textWidth = ClickGui::fontMedium->CalcTextSizeA(18.0f, 400.0f, 0.0f, this->text.toChar()).x;

            if (this->autoSetPos) {
                this->height = 40;
                this->width = textWidth + 40;
            }

            const ImVec2 startPos = ImVec2(winPos.x, winPos.y);
            const ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);
            const ImVec2 textPos = ImVec2(startPos.x + (size.x - textWidth) / 2.0f, startPos.y - 2.0f + (size.y - ImGui::GetFontSize()) / 2.0f);

            if (this->background->isEnabled()) {
                const float rounding = this->rounded->isEnabled() ? ClientUtils::gui_rounding : 0;

                ImGui::GetWindowDrawList()->AddRectFilled(startPos, endPos, ImGui::GetImColor32(ImGuiCol_ChildBg), rounding * 2.0f);

                if (this->border->isEnabled())
                    ImGui::GetWindowDrawList()->AddRect(ImVec2(startPos.x + 1.0f, startPos.y + 1.0f), ImVec2(endPos.x - 1.0f, endPos.y - 1.0f), ImGui::GetImColor32(ImGuiCol_Border), rounding, 0, 2.0f);
            }

            ImGui::GetWindowDrawList()->AddText(ClickGui::fontMedium, 18.0f, textPos, ImGui::GetImColor32(ImGuiCol_Text), this->text.toChar());
        }

        ImGui::End();
    }

    ImVec4 getBackground() const {
        const float* col = ClientUtils::clientColor;

        return {
            col[0], col[1], col[2], (90.0f / 255.0f)
        };
    }

    ImColor32 getFont() const {
        return IM_COL32_WHITE;
    }

    // Void that is called to draw infos on hud
    virtual void renderMod() {
        // Override this method if needed
    }

};

#endif //NEWABYSS_HUDMODULE_H