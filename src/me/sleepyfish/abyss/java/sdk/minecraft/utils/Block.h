// class by sleepyfish for abyss recode
// March 2024 Sunday 5:06 PM

#ifndef NEWABYSS_BLOCK_H
#define NEWABYSS_BLOCK_H

#include "../../SdkClass.h"

struct Block : SdkClass {
    Block(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    String getLocalizedName();

    jboolean isAirBlock();
};

#endif //NEWABYSS_BLOCK_H