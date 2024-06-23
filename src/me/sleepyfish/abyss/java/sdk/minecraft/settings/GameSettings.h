// class by sleepyfish for abyss recode
// February 2024 Thursday 2:55 AM

#ifndef NEWABYSS_GAMESETTINGS_H
#define NEWABYSS_GAMESETTINGS_H

#include "../../SdkClass.h"

struct GameSettings : SdkClass {
    GameSettings(jobject instance);

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    jfloat getFOV();
    void setFOV(jfloat value);

    jfloat getGamma();
    void setGamma(jfloat value);

    void setKeybind(const std::string& mappingName, jboolean state);
    jboolean isKeybindPressed(const std::string& mappingName);
    jobject getKeybind(const std::string& mappingName);

    jfloat getSensitivity();
};

#endif //NEWABYSS_GAMESETTINGS_H