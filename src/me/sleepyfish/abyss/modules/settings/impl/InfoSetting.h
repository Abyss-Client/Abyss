// class by sleepyfish for abyss recode
// February 2024 Wednesday 5:50 AM

#ifndef NEWABYSS_INFOSETTING_H
#define NEWABYSS_INFOSETTING_H

#include "../Setting.h"

class InfoSetting : public Setting {

public:
    InfoSetting(const String text) :
        Setting(text, 6)
    {};

};

#endif //NEWABYSS_INFOSETTING_H