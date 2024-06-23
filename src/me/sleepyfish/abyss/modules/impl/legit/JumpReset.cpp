// class by sleepyfish for abyss recode
// February 2024 Tuesday 5:05 PM

#include "JumpReset.h"
#include "../../../utils/Utils.h"
#include "../../settings/impl/SpaceSetting.h"

JumpReset::JumpReset() : Module("Jump Reset", Category::Legit, "Reduce knockback by jumping while getting hit") {
    this->addSetting(JumpReset::actionMode);
    this->addSetting(JumpReset::hurtTick);
    this->addSetting(JumpReset::sneakWaitTime);
    this->addSetting(new SpaceSetting());
    this->addSetting(JumpReset::weaponOnly);
    this->addSetting(JumpReset::lookingOnly);
    this->addSetting(JumpReset::onlyHolding);
    this->addSetting(JumpReset::sneakFirst);
    this->addSetting(JumpReset::onlyOnce);

    JumpReset::hurtTick->shouldFormat = true;
    JumpReset::sneakWaitTime->shouldFormat = true;
}

void JumpReset::onTick() {

    if (JumpReset::onlyHolding->isEnabled()) {
        if (!Utils::holdingLeft())
            return;
    }

    if (JumpReset::weaponOnly->isEnabled()) {
        if (!Utils::holdingWeapon())
             return;
    }

    if (JumpReset::lookingOnly->isEnabled()) {
        if (Abyss::minecraft->getPointedEntity().isNull())
            return;
    }

    if (JumpReset::onlyOnce->isEnabled()) {
        if (JumpReset::calledOnce) {
            if (Abyss::minecraft->thePlayer->getHurtTime() < JumpReset::hurtTick->getValue())
                JumpReset::calledOnce = false;

            return;
        }
    }

    if (Abyss::minecraft->thePlayer->getHurtTime() < JumpReset::hurtTick->getValue())
        return;

    const std::string currentMode = JumpReset::actionMode->getMode().toString();

    if (currentMode == "Jump") {
        if (Abyss::minecraft->thePlayer->onGround()) {
            Abyss::minecraft->thePlayer->jump();
            JumpReset::calledOnce = true;
        }

        return;
    }

    const int delay = JumpReset::sneakWaitTime->getValue();

    if (currentMode == "Sneak") {
        JumpReset::setSneak(true);
        Sleep(delay);
        JumpReset::setSneak(false);

        JumpReset::calledOnce = true;
        return;
    }

    if (currentMode == "Both") {
        if (JumpReset::sneakFirst->isEnabled()) {
            JumpReset::setSneak(true);
            Sleep(delay);
            JumpReset::setSneak(false);

            if (Abyss::minecraft->thePlayer->onGround())
                Abyss::minecraft->thePlayer->jump();
        } else {
            if (Abyss::minecraft->thePlayer->onGround())
                Abyss::minecraft->thePlayer->jump();

            JumpReset::setSneak(true);
            Sleep(delay);
            JumpReset::setSneak(false);
        }

        JumpReset::calledOnce = true;
        return;
    }
}

void JumpReset::setSneak(const jboolean state) {
    Abyss::minecraft->gameSettings->setKeybind("Sneak", state);
}