// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#ifndef NEWABYSS_JAVA_H
#define NEWABYSS_JAVA_H

#include <vector>
#include "../utils/type/Class.h"
#include "../utils/type/String.h"
#include "../../../../../libraries/jni/jni.h"

class Java : public Class {

public:
    std::vector<String> loadedClients;

    void inject() override;
    void unInject() override;

    bool assignClass(String name, jclass& out);

    void injectJavaEnv();
    void setupClassLoader();
    void checkForMappings();

    void callGarbageCollector();
};

#endif //NEWABYSS_JAVA_H