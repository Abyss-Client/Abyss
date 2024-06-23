// class by sleepyfish for abyss recode
// March 2024 Sunday 4:57 PM

#ifndef NEWABYSS_MOVINGOBJECTPOSITION_H
#define NEWABYSS_MOVINGOBJECTPOSITION_H

#include "../../SdkClass.h"
#include "BlockPos.h"

struct MovingObjectPosition : SdkClass {
    MovingObjectPosition(jobject instance);
    const char* mappingForPosition;

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    jboolean isTypeOfBlock();
    jboolean isTypeOfEntity();
    BlockPos getBlockPos();
};

#endif //NEWABYSS_MOVINGOBJECTPOSITION_H