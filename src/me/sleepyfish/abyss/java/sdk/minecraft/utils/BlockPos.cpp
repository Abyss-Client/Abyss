// class by sleepyfish for abyss recode
// March 2024 Sunday 5:02 PM

#include "BlockPos.h"
#include "../../../../client/Abyss.h"

BlockPos::BlockPos(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["BlockPos"];
    this->instanceObject = instance;
}

jclass BlockPos::getInstanceClass() {
    return this->instanceClass;
}

jobject BlockPos::getInstanceObject() {
    return this->instanceObject;
}

Vector3 BlockPos::getPosition() {
    if (this->isNull()) {
        return { 0, 0, 0 };
    } else {
        return {
            (jfloat) this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["blockPos_x"]),
            (jfloat) this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["blockPos_y"]),
            (jfloat) this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["blockPos_z"])
        };
    }
}

Block BlockPos::getBlock() {
    jmethodID constructor = EnvUtils::Env->GetMethodID(this->getInstanceClass(), "<init>", "(DDD)V");

    if (constructor != nullptr) {
        jobject blockPosObj = this->newObject(this->getInstanceClass(), constructor, getPosition().x, getPosition().y, getPosition().z);
        if (blockPosObj == nullptr)
            return nullptr;

        jobject blockState = this->getObjectMethodArgs(Abyss::minecraft->getInstanceObject(), Mapper::mapper_voids["world_getBlockState"], blockPosObj);

        this->deleteRef(blockPosObj);

        return {
            this->getObjectMethod(blockState, Mapper::mapper_voids["iBlockState_getBlock"])
        };
    }

    return nullptr;
}