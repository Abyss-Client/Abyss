// class by sleepyfish for abyss recode
// February 2024 Wednesday 4:14 AM

#ifndef NEWABYSS_ENVUTILS_H
#define NEWABYSS_ENVUTILS_H

#include "../../../../../libraries/jni/jni.h"
#include "../../../../../libraries/jni/jvmti.h"

class EnvUtils {

public:
    static inline JNIEnv* Env = nullptr;

    static inline jvmtiEnv* JVMti = nullptr;
};

#endif //NEWABYSS_ENVUTILS_H