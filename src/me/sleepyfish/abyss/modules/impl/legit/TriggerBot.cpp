// class by sleepyfish for abyss recode
// February 2024 Wednesday 12:33 AM

#include "TriggerBot.h"
#include "../../settings/impl/SpaceSetting.h"
#include "../../../utils/Utils.h"

TriggerBot::TriggerBot() : Module("Trigger Bot", Category::Legit, "Attacks the target that you are looking at") {
    this->addSetting(TriggerBot::cpsMin);
    this->addSetting(TriggerBot::cpsMax);
    this->addSetting(TriggerBot::extraRandom);
    this->addSetting(TriggerBot::weaponOnly);
    this->addSetting(TriggerBot::onlyHolding);
    this->addSetting(new SpaceSetting());
    this->addSetting(TriggerBot::ignoreFriends);
    this->addSetting(TriggerBot::ignoreInvis);
    this->addSetting(TriggerBot::ignoreBots);

    TriggerBot::cpsMin->shouldFormat = true;
    TriggerBot::cpsMax->shouldFormat = true;

    TriggerBot::clickUtils = new ClickUtils(0);
    TriggerBot::clickUtils->init();
}

void TriggerBot::onTick() {
    if (ClickGui::isGuiOpen)
        return;

    if (TriggerBot::weaponOnly->isEnabled()) {
        if (!Utils::holdingWeapon())
            return;
    }

    if (TriggerBot::onlyHolding->isEnabled()) {
        if (!Utils::holdingLeft())
            return;
    }

    Entity target = Abyss::minecraft->getPointedEntity();

    if (!target.isNull()) {
        if (TriggerBot::ignoreBots->isEnabled()) {
            if (Utils::ignoreTarget(target, TriggerBot::ignoreFriends->isEnabled()))
                return;
        } else {
            if (TriggerBot::ignoreInvis->isEnabled()) {
                if (target.isInvisible())
                    return;
            }
        }

        TriggerBot::clickUtils->update(TriggerBot::cpsMin->getValue(), TriggerBot::cpsMax->getValue(), TriggerBot::extraRandom->isEnabled());
        return;
    }

}