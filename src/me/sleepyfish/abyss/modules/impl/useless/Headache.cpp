// class by sleepyfish for abyss recode
// February 2024 Saturday 12:22 PM

#include "Headache.h"
#include "../../../client/Abyss.h"
#include "../../../gui/ClickGui.h"

bool wasEnabled = false;
Headache::Headache() : Module("Headache", Category::Useless, "Get your free headache here") {}

void Headache::onEnableEvent() {
    Headache::oldFOV = Abyss::minecraft->gameSettings->getFOV();
    Abyss::minecraft->gameSettings->setFOV(1000.0f);
    wasEnabled = true;
}

void Headache::onDisableEvent() {
    if (wasEnabled)
        Abyss::minecraft->gameSettings->setFOV(Headache::oldFOV);
}

void Headache::onTick() {
    Abyss::minecraft->thePlayer->setHeadRotations(-Abyss::minecraft->thePlayer->getRotation().x);
}

void Headache::onRenderTick() {
    ImGui::SetNextWindowPos(ClientUtils::getWindowPosMin());
    ImGui::SetNextWindowSize(ClientUtils::getWindowPosMax());

    ImGui::Begin("Headache goofy ahh", 0, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);

    // render goofy ahh rainbow rectangle that covers the whole screen
    const ImVec4 nig = ColorUtils::getRainbow(40.0f, 100.0f, 1000.0f, 0.4f);
    ImGui::GetWindowDrawList()->AddRectFilled(ClientUtils::getWindowPosMin(), ClientUtils::getWindowPosMax(), ImGui::GetImColor32(nig), 0.0f);

    ImGui::End();
}