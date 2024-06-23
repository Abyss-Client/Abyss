// class by sleepyfish for abyss recode
// February 2024 Thursday 4:30 AM

#include "JavaString.h"



JavaString::JavaString(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["JavaString"];
    this->instanceObject = instance;
}

JavaString::JavaString(std::string text) {
    this->instanceClass = Mapper::mapper_classes["JavaString"];
    this->instanceObject = (jobject) this->getString(text);
}

jclass JavaString::getInstanceClass() {
    return instanceClass;
}

jobject JavaString::getInstanceObject() {
    return this->instanceObject;
}

String JavaString::toString() {
    auto jStr = (jstring) this->getInstanceObject();
    const char* nativeStr = this->getChars(jStr);
    this->releaseString(jStr, nativeStr);
    this->deleteRef(jStr);
    this->deleteRef(this->instanceObject);
    this->deleteRef(this->instanceClass);
    return nativeStr;
}