// class by sleepyfish for abyss recode
// February 2024 Saturday 6:29 AM

#ifndef NEWABYSS_PLAYEROVERLAY_H
#define NEWABYSS_PLAYEROVERLAY_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"

class PlayerOverlay : public Module {

public:
    PlayerOverlay();

    void onEnableEvent() override;
    void onRenderTick() override;

    BoolSetting* darkerBackground = new BoolSetting("Darker Background", false);
};

#endif //NEWABYSS_PLAYEROVERLAY_H