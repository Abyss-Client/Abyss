// class by sleepyfish for abyss recode
// March 2024 Saturday 12:03 AM

#ifndef NEWABYSS_SPIN_H
#define NEWABYSS_SPIN_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"

class Spin : public Module {

public:
    Spin();

    void onTick() override;
    void onGuiRenderTick() override;

    BoolSetting* body = new BoolSetting("Body", "Rotates the body", true);
    BoolSetting* head = new BoolSetting("Head", "Rotates the head", true);
    BoolSetting* revert = new BoolSetting("Revert Rotations", "Revert the rotation for head", true);
    BoolSetting* ignoreGui = new BoolSetting("Ignore Gui State", "Also works while ur in a Gui", false);
};

#endif //NEWABYSS_SPIN_H