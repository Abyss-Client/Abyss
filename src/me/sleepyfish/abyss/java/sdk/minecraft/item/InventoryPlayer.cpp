// class by sleepyfish for abyss recode
// February 2024 Thursday 4:42 AM

#include "InventoryPlayer.h"

InventoryPlayer::InventoryPlayer(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["InventoryPlayer"];
    this->instanceObject = instance;
}

jclass InventoryPlayer::getInstanceClass() {
    return this->instanceClass;
}

jobject InventoryPlayer::getInstanceObject() {
    return this->instanceObject;
}

ItemStack InventoryPlayer::getCurrentItem() {
    return {
        this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["inventoryPlayer_getCurrentItem"])
    };
}

void InventoryPlayer::setCurrentItem(jint index) {
    this->setIntField(this->getInstanceObject(), Mapper::mapper_fields["inventoryPlayer_currentItem"], index);
}

jint InventoryPlayer::getCurrentItemInt() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["inventoryPlayer_currentItem"]);
}

ItemStack InventoryPlayer::getIndexItem(jint index) {
    jobject mainInventory = this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["inventoryPlayer_mainInv"]);
    jobject itemStack = this->getItemInArray((jobjectArray) mainInventory, index);
    this->deleteRef(mainInventory);

    return {
        itemStack
    };
}

ItemStack InventoryPlayer::getArmorItem(jint index) {
     jobject armorInventory = this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["inventoryPlayer_armorInv"]);
     jobject itemStack = this->getItemInArray((jobjectArray) armorInventory, index);
     this->deleteRef(armorInventory);

    return {
        itemStack
    };
}