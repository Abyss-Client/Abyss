// class by sleepyfish for abyss recode
// February 2024 Tuesday 5:05 PM

#ifndef NEWABYSS_JUMPRESET_H
#define NEWABYSS_JUMPRESET_H

#include "../../Module.h"
#include "../../settings/impl/ModeSetting.h"
#include "../../settings/impl/SliderSetting.h"
#include "../../settings/impl/BoolSetting.h"

class JumpReset : public Module {

public:
    JumpReset();

    void onTick() override;

    const std::vector<String> actionModes {
            "Jump", "Sneak", "Both"
    };

    ModeSetting*   actionMode       = new ModeSetting  ("Mode", actionModes, "Jump");
    SliderSetting* hurtTick         = new SliderSetting("Hurt Tick", "The lower the value the more blatant", 8, 1, 10);
    SliderSetting* sneakWaitTime    = new SliderSetting("UnSneak Time", "Time format: ms", 100, 80, 320);
    // Space setting
    BoolSetting* weaponOnly         = new BoolSetting("Weapon Only", "Only works when holding a weapon", true);
    BoolSetting* lookingOnly        = new BoolSetting("Looking Only", "Only works when looking at a player", false);
    BoolSetting* onlyHolding        = new BoolSetting("Hold Only", "Only works when holding", false);
    BoolSetting* sneakFirst         = new BoolSetting("Sneak First", "First sneak then Jump", false);
    BoolSetting* onlyOnce           = new BoolSetting("Only once", "Only jump once (Leave enabled if you dont know what this is doing)", true);

    bool calledOnce = false;
    void setSneak(jboolean state);
};

#endif //NEWABYSS_JUMPRESET_H