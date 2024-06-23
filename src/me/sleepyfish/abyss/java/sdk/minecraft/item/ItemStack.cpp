// class by sleepyfish for abyss recode
// February 2024 Thursday 4:22 AM

#include "ItemStack.h"
#include "../../java/JavaString.h"

ItemStack::ItemStack() {
    this->instanceClass = Mapper::mapper_classes["ItemStack"];
    this->instanceObject = nullptr;
}

ItemStack::ItemStack(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["ItemStack"];
    this->instanceObject = instance;
}

jclass ItemStack::getInstanceClass() {
    return this->instanceClass;
}

jobject ItemStack::getInstanceObject() {
    return this->instanceObject;
}

Item ItemStack::getItem() {
    return this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["itemStack_getItem"]);
}

String ItemStack::getName() {
    JavaString str = JavaString(this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["itemStack_getName"]));

    if (str.isNull())
        return "null";

    return str.toString();
}