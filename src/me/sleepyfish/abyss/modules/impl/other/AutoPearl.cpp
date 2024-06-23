// class by sleepyfish for abyss recode
// March 2024 Monday 6:52 PM

#include "AutoPearl.h"
#include "../../../client/Abyss.h"
#include "../../../utils/Utils.h"

AutoPearl::AutoPearl() : Module("Auto Pearl", Category::Other, "Auto switch to a item while falling") {
    this->addSetting(AutoPearl::itemMode);
    this->addSetting(AutoPearl::fallDistance);
    this->addSetting(AutoPearl::leaveWhenNoItem);

    AutoPearl::fallDistance->shouldFormat = true;
}

void AutoPearl::onTick() {

    if (Abyss::minecraft->thePlayer->getFallDistance() > AutoPearl::fallDistance->getValue()) {
        // if (Utils::overAir(50.0))
        // 	return;

        const String currentMode = AutoPearl::itemMode->getMode();

        if (currentMode.equals("Pearl")) {
            if (!Utils::switchTo("ender ")) {
                if (AutoPearl::leaveWhenNoItem->isEnabled())
                    Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
            }

            return;
        }

        if (currentMode.equals("Water Bucket")) {
            if (!Utils::switchTo("water bu")) {
                if (AutoPearl::leaveWhenNoItem->isEnabled())
                    Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
            }

            return;
        }

        if (currentMode.equals("Web")) {
            if (!Utils::switchTo("cobweb")) {
                if (AutoPearl::leaveWhenNoItem->isEnabled())
                    Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
            }

            return;
        }

        if (currentMode.equals("Bed")) {
            if (!Utils::switchTo("bed")) {
                if (AutoPearl::leaveWhenNoItem->isEnabled())
                    Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
            }

            return;
        }

        if (currentMode.equals("Any without Pearl")) {
            if (!Utils::switchTo("water bu")) {
                if (!Utils::switchTo("cobweb")) {
                    if (!Utils::switchTo("bed")) {
                        if (AutoPearl::leaveWhenNoItem->isEnabled())
                            Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
                    }
                }
            }

            return;
        }

        if (currentMode.equals("Any Item")) {
            if (!Utils::switchTo("ender ")) {
                if (!Utils::switchTo("water bu")) {
                    if (!Utils::switchTo("cobweb")) {
                        if (!Utils::switchTo("bed")) {
                            if (AutoPearl::leaveWhenNoItem->isEnabled())
                                Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
                        }
                    }
                }
            }

            return;
        }
    }

}