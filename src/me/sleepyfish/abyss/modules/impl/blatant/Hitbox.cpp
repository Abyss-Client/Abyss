// class by sleepyfish for abyss recode
// March 2024 Thursday 12:10 AM

#include "Hitbox.h"
#include "../../../utils/Utils.h"

Hitbox::Hitbox() : Module("Hitbox", Category::Blatant, "Expand every hitbox") {
}

void Hitbox::onTick() {

    for (EntityPlayer player : Abyss::minecraft->theWorld->getPlayerList().getVector()) {

    }

}