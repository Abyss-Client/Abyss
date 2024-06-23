    // class by sleepyfish for abyss recode
// March 2024 Sunday 5:02 PM

#ifndef NEWABYSS_BLOCKPOS_H
#define NEWABYSS_BLOCKPOS_H

#include "../../SdkClass.h"
#include "../../../../utils/type/Vector3.h"
#include "Block.h"

struct BlockPos : SdkClass {
    BlockPos(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    Vector3 getPosition();
    Block getBlock();
};

#endif //NEWABYSS_BLOCKPOS_H