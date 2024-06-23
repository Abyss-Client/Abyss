// class by sleepyfish for abyss recode
// February 2024 Tuesday 8:20 PM

#ifndef NEWABYSS_TEAM_H
#define NEWABYSS_TEAM_H

#include "../../SdkClass.h"

struct Team : SdkClass {

public:
    Team(jobject instance);

     jclass getInstanceClass() override;
     jobject getInstanceObject() override;
};

#endif //NEWABYSS_TEAM_H