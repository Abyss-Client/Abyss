// class by sleepyfish for abyss recode
// February 2024 Saturday 12:22 PM

#ifndef NEWABYSS_HEADACHE_H
#define NEWABYSS_HEADACHE_H

#include "../../Module.h"

class Headache : public Module {

public:
    Headache();

    void onEnableEvent() override;
    void onDisableEvent() override;
    void onTick() override;
    void onRenderTick() override;

    jfloat oldFOV = 0.0f;
};

#endif //NEWABYSS_HEADACHE_H