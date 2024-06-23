// class by sleepyfish for abyss recode
// February 2024 Saturday 6:29 AM

#include "Overlay.h"
#include "../../../gui/ClickGui.h"
#include "../../../utils/ClientUtils.h"
#include "../../../utils/opengl/TextureUtils.h"

Overlay::Overlay() : Module("Overlay", Category::Visual, "Render client overlay") {
    this->addSetting(Overlay::renderName);
    this->addSetting(Overlay::renderIcon);
    this->addSetting(Overlay::renderFps);
}

void Overlay::onRenderTick() {
    ImGui::Begin("Overlay Gui", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
    ImDrawList* list = ImGui::GetWindowDrawList();

    const float windowX = ImGui::GetWindowPos().x;
    const float windowY = ImGui::GetWindowPos().y;

    String clientInfo;
    String fps = std::to_string((int) ImGui::GetIO().Framerate);

    if (Overlay::renderName->isEnabled())
        clientInfo = ClientUtils::getNameWithVersion();

    if (Overlay::renderFps->isEnabled()) {
        if (!Overlay::renderName->isEnabled()) {
            clientInfo = String("FPS: ") + fps;
        } else {
            clientInfo = clientInfo + " | Fps: " + fps;
        }
    }

    if (Overlay::renderIcon->isEnabled()) {
        ImGui::SetOffset(15, 15);
        TextureUtils::renderAbyssLogo(64.0f, 64.0f);
    }

    if (Overlay::renderName->isEnabled() || Overlay::renderFps->isEnabled()) {
        const float startX = 85.0f + windowX;
        const float endX = 170.0f;

        const float startY = 30.0f + windowY;
        const float endY = 25.0f;

        ClickGui::renderShadow(ImVec2(startX, startY), ImVec2(startX + endX, startY + endY));
        list->AddRectFilled(ImVec2(startX, startY), ImVec2(startX + endX, startY + endY), ImGui::GetImColor32(ImGuiCol_Border), ClientUtils::gui_rounding);
        const char *ab = clientInfo.toChar();
        list->AddText(ClickGui::fontDefault, 20.0f, ImVec2(startX + 9.0f, startY + 2.0f), IM_COL32_WHITE, ab);
        ImGui::Text("                                                                      ");
    }

    ImGui::End();
}