// class by sleepyfish for abyss recode
// February 2024 Wednesday 12:33 AM

#ifndef NEWABYSS_TRIGGERBOT_H
#define NEWABYSS_TRIGGERBOT_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"
#include "../../settings/impl/SliderSetting.h"
#include "../../../utils/ClickUtils.h"

class TriggerBot : public Module {

public:
    TriggerBot();

    void onTick() override;

    ClickUtils* clickUtils{};

    SliderSetting* cpsMin = new SliderSetting("Cps Min", "Min clicks per second", 8, 1, 20);
    SliderSetting* cpsMax = new SliderSetting("Cps Max", "Max clicks per second", 13, 2, 22);
    BoolSetting* extraRandom = new BoolSetting("Extra Randomization", "Randomize from Min, Max (Original Value) to + 2 and - 2", true);
    BoolSetting* weaponOnly = new BoolSetting("Weapon Only", "Only works when holding a weapon", true);
    BoolSetting* onlyHolding = new BoolSetting("Hold Only", "Only works when holding", false);
    // Space setting
    BoolSetting* ignoreFriends = new BoolSetting("Ignore Friends", "Ignore your Team and added friends", true);
    BoolSetting* ignoreInvis = new BoolSetting("Ignore Invis", "Ignore invisable players", true);
    BoolSetting* ignoreBots = new BoolSetting("Ignore Bots", "Ignore bots", true);

};

#endif //NEWABYSS_TRIGGERBOT_H