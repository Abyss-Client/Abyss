// class by sleepyfish for abyss recode
// March 2024 Saturday 12:03 AM

#include "Spin.h"
#include "../../../client/Abyss.h"

Spin::Spin() : Module("Spin", Category::Useless, "You spin my head right round right round") {
    this->addSetting(Spin::body);
    this->addSetting(Spin::head);
    this->addSetting(Spin::revert);
    this->addSetting(Spin::ignoreGui);
}

jfloat rotateBody = 0.0f;
jfloat rotateHead = 0.0f;

void Spin::onGuiRenderTick() {
    this->ignoreGuiState = Spin::ignoreGui->isEnabled();
}

void Spin::onTick() {
    if (Spin::body->isEnabled()) {
        Abyss::minecraft->thePlayer->setRenderYawOffset(rotateBody);

        if (Spin::revert->isEnabled()) {
            rotateBody--;
        } else {
            rotateBody++;
        }
    }

    if (Spin::head->isEnabled()) {
        Abyss::minecraft->thePlayer->setHeadRotations(rotateHead++);
    }

}