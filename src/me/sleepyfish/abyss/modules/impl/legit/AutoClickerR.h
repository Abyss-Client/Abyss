// class by sleepyfish for abyss recode
// February 2024 Saturday 11:03 AM

#ifndef NEWABYSS_AUTOCLICKER_H
#define NEWABYSS_AUTOCLICKER_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"
#include "../../settings/impl/SliderSetting.h"
#include "../../../utils/ClickUtils.h"

class AutoClickerR : public Module {

public:
    AutoClickerR();

    void onTick() override;

    ClickUtils* clickUtils{};

    SliderSetting* cpsMin = new SliderSetting("Cps Min", "Min clicks per second", 8, 1, 20);
    SliderSetting* cpsMax = new SliderSetting("Cps Max", "Max clicks per second", 13, 2, 22);
    BoolSetting* extraRandom = new BoolSetting("Extra Randomization", "Randomize from Min, Max (Original Value) to + 2 and - 2", true);
    BoolSetting* blockOnly  = new BoolSetting("Blocks Only", "Only works when holding a block", true);
    BoolSetting* lookingOnly = new BoolSetting("Looking Only", "Only works when looking at a block", false);
};

#endif //NEWABYSS_AUTOCLICKER_H