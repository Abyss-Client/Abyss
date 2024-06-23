// class by sleepyfish for abyss recode
// February 2024 Thursday 4:22 AM

#ifndef NEWABYSS_ITEMSTACK_H
#define NEWABYSS_ITEMSTACK_H

#include "../../SdkClass.h"
#include "Item.h"

struct ItemStack : SdkClass {
    ItemStack();
    ItemStack(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    Item getItem();
    String getName();
};

#endif //NEWABYSS_ITEMSTACK_H