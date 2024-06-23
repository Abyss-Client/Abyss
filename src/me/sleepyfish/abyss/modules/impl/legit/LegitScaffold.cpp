// class by sleepyfish for abyss recode
// February 2024 Wednesday 2:48 PM

#include "LegitScaffold.h"
#include "../../../client/Abyss.h"
#include "../../../utils/Utils.h"

LegitScaffold::LegitScaffold() : Module("Legit Scaffold", Category::Legit, "Also Called 'Eagle'") {
    this->addSetting(LegitScaffold::blockOnly);
    this->addSetting(LegitScaffold::lookingOnly);
    this->addSetting(LegitScaffold::onlyHolding);
    this->addSetting(LegitScaffold::onlyLookingDown);
}

void LegitScaffold::onTick() {
    if (LegitScaffold::blockOnly->isEnabled()) {
        if (!Utils::holdingBlock())
            return;
    }

    if (LegitScaffold::onlyHolding->isEnabled()) {
        if (!Utils::holdingRight())
            return;
    }

    if (LegitScaffold::onlyLookingDown->isEnabled()) {
        if (Abyss::minecraft->thePlayer->getRotation().y <= 65.0f)
            return;
    }

    if (LegitScaffold::lookingOnly->isEnabled()) {
        if (!Abyss::minecraft->getObjectMouseOver().isNull())
            return;
    }

    if (Utils::overAir(1)) {
        setSneak(true);
    } else {
        setSneak(false);
    }
}

void LegitScaffold::setSneak(const jboolean state) {
    Abyss::minecraft->gameSettings->setKeybind("Sneak", state);
}