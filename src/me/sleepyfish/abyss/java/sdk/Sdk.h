// class by sleepyfish for abyss recode
// February 2024 Friday 8:43 AM

#ifndef NEWABYSS_SDK_H
#define NEWABYSS_SDK_H

#include "../../utils/type/Class.h"
#include "../mapper/Mapper.h"

class Sdk : public Class {

public:
    void inject() override;
    void unInject() override;
};

#endif //NEWABYSS_SDK_H