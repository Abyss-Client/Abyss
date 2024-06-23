// class by sleepyfish for abyss recode
// February 2024 Thursday 4:42 AM

#ifndef NEWABYSS_INVENTORYPLAYER_H
#define NEWABYSS_INVENTORYPLAYER_H

#include "../../SdkClass.h"
#include "ItemStack.h"

struct InventoryPlayer : SdkClass {
    InventoryPlayer(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    ItemStack getCurrentItem();
    void setCurrentItem(jint index);
    jint getCurrentItemInt();
    ItemStack getIndexItem(jint index);
    ItemStack getArmorItem(jint index);
};

#endif //NEWABYSS_INVENTORYPLAYER_H