// class by sleepyfish for abyss recode
// February 2024 Thursday 2:11 AM

#ifndef NEWABYSS_ENTITYPLAYER_H
#define NEWABYSS_ENTITYPLAYER_H

#include "EntityLivingBase.h"
#include "../item/InventoryPlayer.h"

struct EntityPlayer : EntityLivingBase {
    EntityPlayer();
    EntityPlayer(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    jboolean isSpectator();
    jboolean isBlocking();

    InventoryPlayer getInventory();
};

#endif //NEWABYSS_ENTITYPLAYER_H