#pragma once

#include "../SdkClass.h"

struct JavaList : SdkClass {
    JavaList(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

	jobjectArray toArray();
};