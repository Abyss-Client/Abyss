// class by sleepyfish for abyss recode
// February 2024 Thursday 1:18 AM

#include "EntityPlayerSP.h"

EntityPlayerSP::EntityPlayerSP() : EntityPlayer() {
    this->instanceClass = Mapper::mapper_classes["EntityPlayerSP"];
    this->instanceObject = nullptr;
}

EntityPlayerSP::EntityPlayerSP(jobject instance) : EntityPlayer(instance) {
    this->instanceClass = Mapper::mapper_classes["EntityPlayerSP"];
    this->instanceObject = this->getObjectField(this->instanceClass, "minecraft_thePlayer", instance);
}

jclass EntityPlayerSP::getInstanceClass() {
    return this->instanceClass;
}

jobject EntityPlayerSP::getInstanceObject() {
    return this->instanceObject;
}