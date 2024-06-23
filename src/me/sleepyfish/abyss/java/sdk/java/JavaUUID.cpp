// class by sleepyfish for abyss recode
// February 2024 Thursday 2:23 AM

#include "JavaUUID.h"

JavaUUID::JavaUUID(jobject instance) {
    this->instanceObject = instance;
    this->instanceClass = Mapper::mapper_classes["JavaUUID"];
}

jclass JavaUUID::getInstanceClass() {
    return this->instanceClass;
}

jobject JavaUUID::getInstanceObject() {
    return this->instanceObject;
}

jint JavaUUID::getVersion() {
    return this->getIntMethod(this->getInstanceObject(), Mapper::mapper_voids["uuid_getVersion"]);
}