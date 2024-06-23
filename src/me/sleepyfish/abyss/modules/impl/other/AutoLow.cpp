// class by sleepyfish for abyss recode
// March 2024 Monday 7:02 PM

#include "AutoLow.h"
#include "../../../client/Abyss.h"
#include "../../../utils/Utils.h"

AutoLow::AutoLow() : Module("Auto Low", Category::Other, "Do something very fast while beeing low") {
    this->addSetting(AutoLow::minHealth);
    this->addSetting(AutoLow::autoMode);

    AutoLow::minHealth->shouldFormat = true;
}

bool alrDone = false;

void AutoLow::onTick() {

    if (!alrDone) {
        if (Abyss::minecraft->thePlayer->getHealth() < AutoLow::minHealth->getValue()) {
            const String currentMode = AutoLow::autoMode->getMode();

            if (currentMode.equals("Leave")) {
                Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
                alrDone = true;
            }

            if (currentMode.equals("Gap")) {
                if (Utils::switchTo("Golden Apple"))
                    alrDone = true;
            }

            if (currentMode.equals("Pearl")) {
                if (Utils::switchTo("Pearl"))
                    alrDone = true;
            }

            if (currentMode.equals("Water")) {
                if (Utils::switchTo("Water "))
                    alrDone = true;
            }

            if (currentMode.equals("Lava")) {
                if (Utils::switchTo("Lava "))
                    alrDone = true;
            }

            if (currentMode.equals("Sword")) {
                if (Utils::switchTo("Sword "))
                    alrDone = true;
            }

            if (currentMode.equals("Rod")) {
                if (Utils::switchTo("Fishing "))
                    alrDone = true;
            }
        }
    } else {
        if (Abyss::minecraft->thePlayer->getHealth() > AutoLow::minHealth->getValue())
            alrDone = false;
    }

}