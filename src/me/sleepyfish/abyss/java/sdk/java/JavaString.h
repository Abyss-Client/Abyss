// class by sleepyfish for abyss recode
// February 2024 Thursday 4:30 AM

#ifndef NEWABYSS_JAVASTRING_H
#define NEWABYSS_JAVASTRING_H

#include "../SdkClass.h"

struct JavaString : SdkClass {
    JavaString(jobject instance);
    JavaString(std::string text);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    String toString();
};

#endif //NEWABYSS_JAVASTRING_H