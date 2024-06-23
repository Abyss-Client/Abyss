// class by sleepyfish for abyss recode
// March 2024 Wednesday 11:38 PM

#ifndef NEWABYSS_COORDINATES_H
#define NEWABYSS_COORDINATES_H

#include "../../HudModule.h"

class Coordinates : public HudModule {

public:
    Coordinates();

    void onEnableEvent() override;
    void renderMod() override;
};

#endif //NEWABYSS_COORDINATES_H