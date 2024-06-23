// class by sleepyfish for abyss recode
// February 2024 Sunday 8:59 PM

#ifndef NEWABYSS_SET_H
#define NEWABYSS_SET_H

#include "../../java/sdk/SdkClass.h"
#include "../../client/Abyss.h"

struct Set : SdkClass {

    jmethodID toArrayMethodID;

    /*
    Set(jobject instance) {
        this->instanceObject = instance;

        this->instanceClass = EnvUtils::Env->FindClass("java/util/Set");
        this->toArrayMethodID = EnvUtils::Env->GetMethodID(this->instanceClass, "toArray", "()[Ljava/util/Object;");
    }
    */

    /*
    Set(jobject instance) {
        this->instanceObject = instance;
        this->instanceClass = EnvUtils::Env->FindClass("java/util/Set");

        if (this->instanceClass == nullptr)
            Abyss::logger.log("Failed to create global reference for java/util/Set class");

        this->toArrayMethodID = EnvUtils::Env->GetMethodID(this->instanceClass, "toArray", "()[Ljava/lang/Object;");
        if (this->toArrayMethodID == nullptr)
            Abyss::logger.log("toArray method not found in java/util/Set");
    }
     */

    Set(jobject instance) {
        this->instanceObject = instance;
        this->instanceClass = Mapper::mapper_classes["JavaSet"];

        if (this->instanceClass == nullptr)
            Abyss::logger.log("Failed to find class: java/util/Set");
        else
            Abyss::logger.log("Class java/util/Set found successfully");

        this->toArrayMethodID = EnvUtils::Env->GetMethodID(this->instanceClass, "toArray", "()[Ljava/lang/Object;");
        if (this->toArrayMethodID == nullptr)
            Abyss::logger.log("Method toArray not found in java/util/Set");
        else
            Abyss::logger.log("Method toArray found successfully");
    }

    void inject() override {}
    void unInject() override {}

    jobjectArray toArray() {
        return (jobjectArray) EnvUtils::Env->CallObjectMethod(this->instanceObject, this->toArrayMethodID);
    }

    jint size() {
        const jmethodID sizeMethodID = EnvUtils::Env->GetMethodID(instanceClass, "size", "()I");
        return EnvUtils::Env->CallIntMethod(instanceObject, sizeMethodID);
    }

};

#endif //NEWABYSS_SET_H