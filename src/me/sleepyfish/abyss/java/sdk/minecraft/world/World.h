// class by sleepyfish for abyss recode
// February 2024 Thursday 2:47 AM

#ifndef NEWABYSS_WORLD_H
#define NEWABYSS_WORLD_H

#include "../../SdkClass.h"
#include "../entity/EntityPlayer.h"
#include "../../java/JavaList.h"
#include "../../../../utils/type/ArrayList.h"

struct World : SdkClass {
    World(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    String getName();
    //ArrayList<EntityPlayer> getEntities();
    JavaList getEntities();
    ArrayList<EntityPlayer> getPlayerList();

    jboolean isAirBlock(jdouble x, jdouble y, jdouble z);
};

#endif //NEWABYSS_WORLD_H