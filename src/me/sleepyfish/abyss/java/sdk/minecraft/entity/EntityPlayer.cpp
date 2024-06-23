// class by sleepyfish for abyss recode
// February 2024 Thursday 2:11 AM

#include "EntityPlayer.h"

EntityPlayer::EntityPlayer() : EntityLivingBase() {
    this->instanceClass = Mapper::mapper_classes["EntityPlayer"];
    this->instanceObject = nullptr;
}

EntityPlayer::EntityPlayer(jobject instance) : EntityLivingBase(instance) {
    this->instanceClass = Mapper::mapper_classes["EntityPlayer"];
    this->instanceObject = instance;
}

jclass EntityPlayer::getInstanceClass() {
    return this->instanceClass;
}

jobject EntityPlayer::getInstanceObject() {
    return this->instanceObject;
}

jboolean EntityPlayer::isSpectator() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entityPlayer_isSpectator"]);
}

jboolean EntityPlayer::isBlocking() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entityPlayer_isBlocking"]);
}

InventoryPlayer EntityPlayer::getInventory() {
    return InventoryPlayer(
        this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["entityPlayer_inventory"])
    );
}