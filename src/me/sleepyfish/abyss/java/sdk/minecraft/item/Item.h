// class by sleepyfish for abyss recode
// February 2024 Thursday 4:22 AM

#ifndef NEWABYSS_ITEM_H
#define NEWABYSS_ITEM_H

#include "../../SdkClass.h"

struct Item : SdkClass {
    Item();
    Item(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

};

#endif //NEWABYSS_ITEM_H