// class by sleepyfish for abyss recode
// March 2024 Saturday 11:10 PM

#include "Disabler.h"
#include "../../../utils/ClientUtils.h"

Disabler::Disabler() : Module("Disabler", Category::Useless, "Disables your Minecraft") {
    this->ignoreGuiState = true;
}

void Disabler::onEnableEvent() {
    ClientUtils::crash();
}