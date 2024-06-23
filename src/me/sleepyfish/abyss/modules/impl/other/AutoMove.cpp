// class by sleepyfish for abyss recode
// February 2024 Sunday 2:13 PM

#include "AutoMove.h"
#include "../../../client/Abyss.h"

AutoMove::AutoMove() : Module("Auto Move", Category::Other, "Makes you auto move in a direction given") {
    this->addSetting(AutoMove::walkMode);
    this->addSetting(AutoMove::ignoreGui);
    this->addSetting(AutoMove::sneak);
    this->addSetting(AutoMove::jump);
}

void AutoMove::onGuiRenderTick() {
    this->ignoreGuiState = AutoMove::ignoreGui->isEnabled();
}

void AutoMove::onTick() {
    const std::string currentMode = AutoMove::walkMode->getMode().toString();

    if (AutoMove::sneak->isEnabled()) {
        Abyss::minecraft->gameSettings->setKeybind("Sneak", true);
    }

    if (AutoMove::jump->isEnabled()) {
        Abyss::minecraft->gameSettings->setKeybind("Jump", true);
    }

    if (currentMode == "Forward") {
        Abyss::minecraft->gameSettings->setKeybind("Forward", true);
        return;
    }

    if (currentMode == "Backward") {
        Abyss::minecraft->gameSettings->setKeybind("Back", true);
        return;
    }

    if (currentMode == "Right") {
        Abyss::minecraft->gameSettings->setKeybind("Right", true);
        return;
    }

    if (currentMode == "Right Strafe") {
        Abyss::minecraft->gameSettings->setKeybind("Right", true);
        Abyss::minecraft->gameSettings->setKeybind("Forward", true);
        return;
    }

    if (currentMode == "Left") {
        Abyss::minecraft->gameSettings->setKeybind("Left", true);
        return;
    }

    if (currentMode == "Left Strafe") {
        Abyss::minecraft->gameSettings->setKeybind("Left", true);
        Abyss::minecraft->gameSettings->setKeybind("Forward", true);
        return;
    }

}