// class by sleepyfish for abyss recode
// March 2024 Monday 7:02 PM

#include "Remover.h"
#include "../../../client/Abyss.h"
#include "../../../utils/Utils.h"
#include "../../settings/impl/SpaceSetting.h"

Remover::Remover() : Module("Remover", Category::Other, "Remove Delay") {
    this->addSetting(Remover::removeLeft);
    this->addSetting(Remover::weaponOnly);
    this->addSetting(new SpaceSetting());
    this->addSetting(Remover::removeRight);
    this->addSetting(Remover::blockOnly);
    this->addSetting(Remover::lookingOnly);
}

void Remover::onTick() {
    if (Remover::removeLeft->isEnabled())
        Remover::removeLeftDelay();

    if (Remover::removeRight->isEnabled())
        Remover::removeRightDelay();
}

void Remover::removeLeftDelay() const {
    if (Remover::weaponOnly->isEnabled()) {
        if (!Utils::holdingWeapon())
            return;
    }

    Abyss::minecraft->setLeftClickDelay(0);
}

void Remover::removeRightDelay() const {
    if (Remover::blockOnly->isEnabled()) {
        if (!Utils::holdingBlock())
            return;
    }

    if (Remover::lookingOnly->isEnabled()) {
        if (!Abyss::minecraft->getPointedEntity().isNull())
            return;
    }

    Abyss::minecraft->setRightClickDelay(0);
}