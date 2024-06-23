// class by sleepyfish for abyss recode
// February 2024 Saturday 6:29 AM

#include "PlayerOverlay.h"
#include "../../../gui/ClickGui.h"
#include "../../../utils/Utils.h"

ArrayList<EntityPlayer> playerEntities;
PlayerOverlay::PlayerOverlay() : Module("Player Overlay", Category::Visual, "Render all player Names") {
}

void PlayerOverlay::onEnableEvent() {
    if (!Abyss::minecraft->theWorld->getPlayerList().isEmpty())
        playerEntities = Abyss::minecraft->theWorld->getPlayerList();
}

void PlayerOverlay::onRenderTick() {
    ImGui::Begin("PlayerOverlay Gui", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);

    int offset = 0;

    for (EntityPlayer target : playerEntities.getVector()) {
        if (!target.isNull())
            continue;

        ImGui::Text(target.getName().toChar());
        offset += 18.0f;
    }

    ImGui::End();
}