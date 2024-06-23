// class by sleepyfish for abyss recode
// February 2024 Saturday 11:33 AM

#include "AutoClickerR.h"
#include "../../../utils/Utils.h"

AutoClickerR::AutoClickerR() : Module("Right Clicker", Category::Legit, "Automatically right clicks for you") {
    this->addSetting(AutoClickerR::cpsMin);
    this->addSetting(AutoClickerR::cpsMax);
    this->addSetting(AutoClickerR::extraRandom);
    this->addSetting(AutoClickerR::blockOnly);
    this->addSetting(AutoClickerR::lookingOnly);

    AutoClickerR::cpsMin->shouldFormat = true;
    AutoClickerR::cpsMax->shouldFormat = true;

    AutoClickerR::clickUtils = new ClickUtils(1);
    AutoClickerR::clickUtils->init();
}

void AutoClickerR::onTick() {
    if (ClickGui::isGuiOpen)
        return;

    if (!Utils::holdingRight())
        return;

    if (AutoClickerR::blockOnly->isEnabled()) {
        if (!Utils::holdingBlock())
            return;
    }

    if (AutoClickerR::lookingOnly->isEnabled()) {
        if (!Abyss::minecraft->getPointedEntity().isNull())
            return;
    }

    AutoClickerR::clickUtils->update(AutoClickerR::cpsMin->getValue(), AutoClickerR::cpsMax->getValue(), AutoClickerR::extraRandom->isEnabled());
}