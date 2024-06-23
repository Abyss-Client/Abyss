// class by sleepyfish for abyss recode
// February 2024 Saturday 11:03 AM

#ifndef NEWABYSS_AUTOCLICKERL_H
#define NEWABYSS_AUTOCLICKERL_H

#include "../../Module.h"
#include "../../../utils/ClickUtils.h"
#include "../../settings/impl/BoolSetting.h"
#include "../../settings/impl/SliderSetting.h"

class AutoClickerL : public Module {

public:
    AutoClickerL();

    void onTick() override;

    ClickUtils* clickUtils{};

    SliderSetting* cpsMin = new SliderSetting("Cps Min", "Min clicks per second", 8, 1, 20);
    SliderSetting* cpsMax = new SliderSetting("Cps Max", "Max clicks per second", 13, 2, 22);
    BoolSetting* extraRandom = new BoolSetting("Extra Randomization", "Randomize from Min, Max (Original Value) to + 2 and - 2", true);
    BoolSetting* weaponOnly  = new BoolSetting("Weapon Only", "Only works when holding a weapon", true);
    BoolSetting* lookingOnly = new BoolSetting("Looking Only", "Only works when looking at a player", false);
};

#endif //NEWABYSS_AUTOCLICKERL_H