// class by sleepyfish for abyss recode
// February 2024 Thursday 2:47 AM

#ifndef NEWABYSS_WORLDCLIENT_H
#define NEWABYSS_WORLDCLIENT_H

#include "World.h"
#include "../../../../utils/type/ArrayList.h"

struct WorldClient : World {
    WorldClient(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    void sendQuittingDisconnectingPacket();
    void setWorldTime(jlong value);
};

#endif //NEWABYSS_WORLDCLIENT_H