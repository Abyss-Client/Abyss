// class by sleepyfish for abyss recode
// February 2024 Thursday 2:12 AM

#include "EntityLivingBase.h"
#include "../world/Team.h"

EntityLivingBase::EntityLivingBase() {
    this->instanceClass = Mapper::mapper_classes["EntityLivingBase"];
    this->instanceObject = nullptr;
}

EntityLivingBase::EntityLivingBase(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["EntityLivingBase"];
    this->instanceObject = instance;
}

jclass EntityLivingBase::getInstanceClass() {
    return this->instanceClass;
}

jobject EntityLivingBase::getInstanceObject() {
    return this->instanceObject;
}

jfloat EntityLivingBase::getHealth() {
    return this->getFloatMethod(this->getInstanceObject(), Mapper::mapper_voids["entityLivingBase_getHealth"]);
}

jfloat EntityLivingBase::getMaxHealth() {
    return this->getFloatMethod(this->getInstanceObject(), Mapper::mapper_voids["entityLivingBase_getMaxHealth"]);
}

jfloat EntityLivingBase::getMoveStrafe() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_moveStrafe"]);
}

jfloat EntityLivingBase::getMoveForward() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_moveForward"]);
}

jboolean EntityLivingBase::canEntityBeSeen(Entity entity) {
    return true;

    // crashes in vanilla
    return this->getBooleanMethodArgs(this->getInstanceObject(), Mapper::mapper_voids["entityPlayerBase_canEntityBeSeen"], entity.getInstanceObject());
}

jboolean EntityLivingBase::isPlayerSleeping() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entityPlayerBase_isPlayerSleeping"]);
}

jint EntityLivingBase::getHurtTime() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_hurtTime"]);
}

jint EntityLivingBase::getMaxHurtResistantTime() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_maxHurtResistantTime"]);
}

void EntityLivingBase::swingItem() {
    this->callVoid(this->getInstanceObject(), Mapper::mapper_voids["entityLivingBase_swingItem"]);
}

void EntityLivingBase::jump() {
    this->callVoid(this->getInstanceObject(), Mapper::mapper_voids["entityLivingBase_jump"]);
}

void EntityLivingBase::setHeadRotations(jfloat value) {
    this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_rotationYawHead"], value);
    this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_prevRotationYawHead"], value + 1);
}

void EntityLivingBase::setRenderYawOffset(jfloat value) {
    this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entityLivingBase_renderYawOffset"], value);
}