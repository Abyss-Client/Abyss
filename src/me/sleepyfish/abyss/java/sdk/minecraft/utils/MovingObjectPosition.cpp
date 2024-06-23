// class by sleepyfish for abyss recode
// March 2024 Sunday 4:57 PM

#include "MovingObjectPosition.h"

MovingObjectPosition::MovingObjectPosition(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["MovingObjectPosition"];
    this->instanceObject = instance;

    if (Mapper::currentMapping == Mapper::Mappings::Vanilla) {
        this->mappingForPosition = "Lauh$a;";
    } else {
        this->mappingForPosition = "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;";
    }
}

jclass MovingObjectPosition::getInstanceClass() {
    return this->instanceClass;
}

jobject MovingObjectPosition::getInstanceObject() {
    return this->instanceObject;
}

jboolean MovingObjectPosition::isTypeOfBlock() {
    jobject typeOfHit = EnvUtils::Env->GetObjectField(this->getInstanceObject(), Mapper::mapper_fields["movingObjectPosition_typeOfHit"]);
    jclass movingObjectType = EnvUtils::Env->GetObjectClass(typeOfHit);
    jfieldID block = EnvUtils::Env->GetStaticFieldID(movingObjectType, "BLOCK", this->mappingForPosition);
    jobject object = EnvUtils::Env->GetStaticObjectField(movingObjectType, block);

    const bool isSame = EnvUtils::Env->IsSameObject(object, typeOfHit);
    EnvUtils::Env->DeleteLocalRef(object);
    block = nullptr;
    EnvUtils::Env->DeleteLocalRef(movingObjectType);
    EnvUtils::Env->DeleteLocalRef(typeOfHit);

    return isSame;
}

jboolean MovingObjectPosition::isTypeOfEntity() {
    jobject typeOfHit = EnvUtils::Env->GetObjectField(this->getInstanceObject(), Mapper::mapper_fields["movingObjectPosition_typeOfHit"]);
    jclass movingObjectType = EnvUtils::Env->GetObjectClass(typeOfHit);
    jfieldID entity = EnvUtils::Env->GetStaticFieldID(movingObjectType, "ENTITY", this->mappingForPosition);
    jobject object = EnvUtils::Env->GetStaticObjectField(movingObjectType, entity);

    const bool isSame = EnvUtils::Env->IsSameObject(object, typeOfHit);
    EnvUtils::Env->DeleteLocalRef(object);
    entity = nullptr;
    EnvUtils::Env->DeleteLocalRef(movingObjectType);
    EnvUtils::Env->DeleteLocalRef(typeOfHit);

    return isSame;
}

BlockPos MovingObjectPosition::getBlockPos() {
    return {
        this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["movingObjectPosition_blockPos"])
    };
}