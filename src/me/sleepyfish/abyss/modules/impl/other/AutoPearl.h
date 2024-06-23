// class by sleepyfish for abyss recode
// March 2024 Monday 6:52 PM

#ifndef NEWABYSS_AUTOPEARL_H
#define NEWABYSS_AUTOPEARL_H

#include "../../Module.h"
#include "../../settings/impl/ModeSetting.h"
#include "../../settings/impl/SliderSetting.h"
#include "../../settings/impl/BoolSetting.h"

class AutoPearl : public Module {

public:
    AutoPearl();

    void onTick() override;

    const std::vector<String> ItemModes {
        "Pearl", "Water Bucket", "Web", "Bed", "Any without Pearl", "Any Item"
    };

    ModeSetting* itemMode = new ModeSetting("Item Mode", ItemModes, "Any Item");
    SliderSetting* fallDistance = new SliderSetting("Fall Distance", "The distance you must have been fallen to switch", 6, 5, 20);
    BoolSetting* leaveWhenNoItem = new BoolSetting("Leave game", "Leave the game when no item was found", true);
};

#endif //NEWABYSS_AUTOPEARL_H