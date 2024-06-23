// class by sleepyfish for abyss recode
// February 2024 Thursday 2:23 AM

#ifndef NEWABYSS_JAVAUUID_H
#define NEWABYSS_JAVAUUID_H

#include "../SdkClass.h"

struct JavaUUID : SdkClass {
    JavaUUID(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    jint getVersion();
};

#endif //NEWABYSS_JAVAUUID_H