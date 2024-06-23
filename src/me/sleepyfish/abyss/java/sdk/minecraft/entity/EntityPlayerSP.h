// class by sleepyfish for abyss recode
// February 2024 Thursday 1:18 AM

#ifndef NEWABYSS_ENTITYPLAYERSP_H
#define NEWABYSS_ENTITYPLAYERSP_H

#include "EntityPlayer.h"

struct EntityPlayerSP : EntityPlayer {
    EntityPlayerSP();
    EntityPlayerSP(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;
};

#endif //NEWABYSS_ENTITYPLAYERSP_H