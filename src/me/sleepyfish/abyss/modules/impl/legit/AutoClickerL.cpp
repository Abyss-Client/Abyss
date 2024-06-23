// class by sleepyfish for abyss recode
// February 2024 Saturday 11:03 AM

#include "AutoClickerL.h"
#include "../../../utils/Utils.h"

AutoClickerL::AutoClickerL() : Module("Left Clicker", Category::Legit, "Automatically left clicks for you") {
    this->addSetting(AutoClickerL::cpsMin);
    this->addSetting(AutoClickerL::cpsMax);
    this->addSetting(AutoClickerL::extraRandom);
    this->addSetting(AutoClickerL::weaponOnly);
    this->addSetting(AutoClickerL::lookingOnly);

    AutoClickerL::cpsMin->shouldFormat = true;
    AutoClickerL::cpsMax->shouldFormat = true;

    AutoClickerL::clickUtils = new ClickUtils(0);
    AutoClickerL::clickUtils->init();
}

void AutoClickerL::onTick() {
    if (ClickGui::isGuiOpen)
        return;

    if (!Utils::holdingLeft())
        return;

    if (AutoClickerL::weaponOnly->isEnabled()) {
        if (!Utils::holdingWeapon())
            return;
    }

    if (AutoClickerL::lookingOnly->isEnabled()) {
        if (Abyss::minecraft->getPointedEntity().isNull())
            return;
    }

    AutoClickerL::clickUtils->update(AutoClickerL::cpsMin->getValue(), AutoClickerL::cpsMax->getValue(), AutoClickerL::extraRandom->isEnabled());
}