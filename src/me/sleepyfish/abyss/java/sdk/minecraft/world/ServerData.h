// class by sleepyfish for abyss recode
// March 2024 Friday 11:22 PM

#ifndef NEWABYSS_SERVERDATA_H
#define NEWABYSS_SERVERDATA_H

#include "../../SdkClass.h"

struct ServerData : SdkClass {

public:
    ServerData(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    String getServerIP();

    String getServerName();
};

#endif //NEWABYSS_SERVERDATA_H