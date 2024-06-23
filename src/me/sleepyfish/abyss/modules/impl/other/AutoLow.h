// class by sleepyfish for abyss recode
// March 2024 Monday 7:02 PM

#ifndef NEWABYSS_AUTOLOW_H
#define NEWABYSS_AUTOLOW_H

#include "../../Module.h"
#include "../../settings/impl/SliderSetting.h"
#include "../../settings/impl/ModeSetting.h"

class AutoLow : public Module {

public:
    AutoLow();

    void onTick() override;

    const std::vector<String> AutoModes {
        "Leave", "Gap", "Pearl", "Water", "Lava", "Sword", "Rod"
    };

    SliderSetting* minHealth = new SliderSetting("Min Health", 6, 2, 20);
    ModeSetting* autoMode = new ModeSetting("Mode", AutoModes, "Leave");

};

#endif //NEWABYSS_AUTOLOW_H