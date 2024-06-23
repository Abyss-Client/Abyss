// class by sleepyfish for abyss recode
// February 2024 Sunday 2:12 AM

#ifndef NEWABYSS_SESSION_H
#define NEWABYSS_SESSION_H

#include "../../SdkClass.h"

struct Session : SdkClass {

public:
    Session(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    String getUsername();
    jobject getSessionType();

    void checkForName();
};

#endif //NEWABYSS_SESSION_H