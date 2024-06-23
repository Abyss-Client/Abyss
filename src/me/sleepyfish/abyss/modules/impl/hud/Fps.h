// class by sleepyfish for abyss recode
// March 2024 Wednesday 11:38 PM

#ifndef NEWABYSS_FPS_H
#define NEWABYSS_FPS_H

#include "../../HudModule.h"

class Fps : public HudModule {

public:
    Fps();

    void onEnableEvent() override;
    void renderMod() override;

    BoolSetting* showText = new BoolSetting("Show Text", true);
};

#endif //NEWABYSS_FPS_H