// class by sleepyfish for abyss recode
// February 2024 Thursday 4:22 AM

#include "Item.h"

Item::Item() {
    this->instanceClass = Mapper::mapper_classes["Item"];
    this->instanceObject = nullptr;
}

Item::Item(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["Item"];
    this->instanceObject = instance;
}

jclass Item::getInstanceClass() {
    return this->instanceClass;
}

jobject Item::getInstanceObject() {
    return this->instanceObject;
}