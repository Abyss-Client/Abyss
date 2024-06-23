// class by sleepyfish for abyss recode
// March 2024 Wednesday 11:38 PM

#include "Fps.h"

short updateCounter = 0;
String fpsString;

Fps::Fps() : HudModule("Fps", "Render your Fps on the Hud") {
    this->addSetting(Fps::showText);
}

void Fps::onEnableEvent() {
    fpsString = std::to_string((int) ImGui::GetIO().Framerate);
}

void Fps::renderMod() {
    if (updateCounter != 400) {
        updateCounter++;
    } else {
        fpsString = std::to_string((int) ImGui::GetIO().Framerate);
        updateCounter = 0;
    }

    String finalText = fpsString;

    if (Fps::showText->isEnabled()) {
        finalText = (String) "FPS: " + fpsString;
    }

    this->text = finalText;
}