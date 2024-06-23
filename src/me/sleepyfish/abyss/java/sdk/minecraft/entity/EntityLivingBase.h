// class by sleepyfish for abyss recode
// February 2024 Thursday 2:12 AM

#ifndef NEWABYSS_ENTITYLIVINGBASE_H
#define NEWABYSS_ENTITYLIVINGBASE_H

#include "Entity.h"

struct EntityLivingBase : Entity {
    EntityLivingBase();
    EntityLivingBase(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    void jump();
    void swingItem();
    jboolean isPlayerSleeping();
    jboolean canEntityBeSeen(Entity entity);
    jfloat getHealth();
    jfloat getMaxHealth();
    jint getMaxHurtResistantTime();
    jint getHurtTime();

    jfloat getMoveStrafe();
    jfloat getMoveForward();

    void setHeadRotations(jfloat value);
    void setRenderYawOffset(jfloat value);
};

#endif //NEWABYSS_ENTITYLIVINGBASE_H