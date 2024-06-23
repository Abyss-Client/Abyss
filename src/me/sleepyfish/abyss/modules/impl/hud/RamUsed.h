// class by sleepyfish for abyss recode
// March 2024 Friday 11:20 PM

#ifndef NEWABYSS_RAMUSED_H
#define NEWABYSS_RAMUSED_H

#include "../../HudModule.h"

class RamUsed : public HudModule {

public:
    RamUsed();

    void renderMod() override;

    BoolSetting* showText = new BoolSetting("Show Text", true);
};

#endif //NEWABYSS_RAMUSED_H