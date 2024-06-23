// class by sleepyfish for abyss recode
// March 2024 Friday 11:20 PM

#ifndef NEWABYSS_SERVERIP_H
#define NEWABYSS_SERVERIP_H

#include "../../HudModule.h"

class ServerIP : public HudModule {

public:
    ServerIP();

    void renderMod() override;

    BoolSetting* showText = new BoolSetting("Show Text", true);
};

#endif //NEWABYSS_SERVERIP_H