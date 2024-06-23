// class by sleepyfish for abyss recode
// February 2024 Saturday 12:09 PM

#include "Fullbright.h"
#include "../../../client/Abyss.h"

Fullbright::Fullbright() : Module("Fullbright", Category::Visual, "Makes your game more bright") {
    oldGamma = 0.0f;
}

void Fullbright::onEnableEvent() {
    this->oldGamma = Abyss::minecraft->gameSettings->getGamma();
    Abyss::minecraft->gameSettings->setGamma(1000.0f);
}

void Fullbright::onDisableEvent() {
    Abyss::minecraft->gameSettings->setGamma(this->oldGamma);
    this->oldGamma = 0.0f;
}