// class by sleepyfish for abyss recode
// March 2024 Wednesday 6:45 PM

#include "TimeChanger.h"
#include "../../../client/Abyss.h"

TimeChanger::TimeChanger() : Module("Time Changer", Category::Visual, "Change the world time") {
    this->addSetting(TimeChanger::timeMode);
}

void TimeChanger::onEnableEvent() {
    this->ignoreGuiState = true;
}

void TimeChanger::onTick() {
    const String currentMode = TimeChanger::timeMode->getMode();

    if (currentMode.equals("Dawn")) {
        // Abyss::minecraft->theWorld->setWorldTime(0);
        return;
    }

    if (currentMode.equals("Morning")) {
        // Abyss::minecraft->theWorld->setWorldTime(1000);
        return;
    }

    if (currentMode.equals("Noon")) {
        // Abyss::minecraft->theWorld->setWorldTime(6000);
        return;
    }

    if (currentMode.equals("Afternoon")) {
        // Abyss::minecraft->theWorld->setWorldTime(8000);
        return;
    }

    if (currentMode.equals("Evening")) {
        // Abyss::minecraft->theWorld->setWorldTime(12000);
        return;
    }

    if (currentMode.equals("Dusk")) {
        // Abyss::minecraft->theWorld->setWorldTime(13000);
        return;
    }

    if (currentMode.equals("Night")) {
        // Abyss::minecraft->theWorld->setWorldTime(14000);
        return;
    }

    if (currentMode.equals("Midnight")) {
        // Abyss::minecraft->theWorld->setWorldTime(18000);
        return;
    }

}