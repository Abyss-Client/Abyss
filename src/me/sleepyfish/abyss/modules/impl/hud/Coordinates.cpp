// class by sleepyfish for abyss recode
// March 2024 Wednesday 11:38 PM

#include "Coordinates.h"
#include "../../../client/Abyss.h"

short updateCounterr = 0;
Vector3 pos;

Coordinates::Coordinates() : HudModule("Coordinates", "Render your coordinates on the Hud") {
}

void Coordinates::onEnableEvent() {
    pos = Abyss::minecraft->thePlayer->getPosition();
}

void Coordinates::renderMod() {
    if (updateCounterr != 400) {
        updateCounterr++;
    } else {
        pos = Abyss::minecraft->thePlayer->getPosition();
        updateCounterr = 0;
    }

    const String posX = "X: "   + std::to_string((int) round(pos.x));
    const String posY = ", Y: " + std::to_string((int) round(pos.y));
    const String posZ = ", Z: " + std::to_string((int) round(pos.z));

    this->text = posX + posY + posZ;
}