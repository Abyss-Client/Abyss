// class by sleepyfish for abyss recode
// February 2024 Sunday 2:13 PM

#ifndef NEWABYSS_AUTOMOVE_H
#define NEWABYSS_AUTOMOVE_H

#include "../../Module.h"
#include "../../settings/impl/ModeSetting.h"
#include "../../settings/impl/BoolSetting.h"

class AutoMove : public Module {

public:
    AutoMove();

    void onTick() override;
    void onGuiRenderTick() override;

    const std::vector<String> walkModes {
        "Forward",
        "Backward",
        "Right",
        "Right Strafe",
        "Left",
        "Left Strafe"
    };

    ModeSetting* walkMode = new ModeSetting("Mode", walkModes, "Forward");
    BoolSetting* ignoreGui = new BoolSetting("Ignore Gui State", "Also works while ur in a Gui", false);
    BoolSetting* sneak = new BoolSetting("Sneak", false);
    BoolSetting* jump = new BoolSetting("Jump", false);
};

#endif //NEWABYSS_AUTOMOVE_H