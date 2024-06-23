// class by sleepyfish for abyss recode
// March 2024 Friday 11:20 PM

#ifndef NEWABYSS_SERVERNAME_H
#define NEWABYSS_SERVERNAME_H

#include "../../HudModule.h"

class ServerName : public HudModule {

public:
    ServerName();

    void renderMod() override;

    BoolSetting* showText = new BoolSetting("Show Text", true);
};

#endif //NEWABYSS_SERVERNAME_H