// class by sleepyfish for abyss recode
// February 2024 Thursday 2:13 AM

#ifndef NEWABYSS_ENTITY_H
#define NEWABYSS_ENTITY_H

#include "../../SdkClass.h"
#include "../../../../utils/type/Vector3.h"
#include "../../../../utils/type/Vector2.h"
#include "../world/Team.h"
#include "../../java/JavaUUID.h"

struct Entity : SdkClass {
    Entity();
    Entity(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    String getName();
    jboolean isSneaking();
    void setSneaking(const jboolean state);
    jboolean inWater();
    jboolean isInvisible();

    JavaUUID getUUID();

    Vector3 getEyePosition();
    Vector3 getMotion();
    Vector3 getPosition();
    Vector3 getLastPosition();

    jfloat getWidth();
    jfloat getHeight();

    jint getHurtResistantTime();
    void setRotation(const Vector2 vec, bool save = true);

    Vector2 getRotation();
    jboolean onGround();
    jfloat getFallDistance();
    jint getTicksExisted();
    jboolean isDead();

    Team getTeam();

};

#endif //NEWABYSS_ENTITY_H