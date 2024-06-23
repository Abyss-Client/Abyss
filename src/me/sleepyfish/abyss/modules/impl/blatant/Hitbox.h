// class by sleepyfish for abyss recode
// March 2024 Thursday 12:10 AM

#ifndef NEWABYSS_HITBOX_H
#define NEWABYSS_HITBOX_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"
#include "../../settings/impl/SliderSetting.h"

class Hitbox : public Module {

public:
    Hitbox();

    void onTick() override;

    SliderSetting* range = new SliderSetting("Expand", "Expand the hitbox", 2, 1, 6);
    BoolSetting* weaponOnly = new BoolSetting("Weapon Only", "Only works when holding a weapon", true);
};

#endif //NEWABYSS_HITBOX_H