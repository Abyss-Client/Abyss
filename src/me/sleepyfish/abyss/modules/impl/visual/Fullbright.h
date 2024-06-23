// class by sleepyfish for abyss recode
// February 2024 Saturday 12:09 PM

#ifndef NEWABYSS_FULLBRIGHT_H
#define NEWABYSS_FULLBRIGHT_H

#include "../../Module.h"

class Fullbright : public Module {

public:
    Fullbright();

    void onEnableEvent() override;
    void onDisableEvent() override;

    jfloat oldGamma = 0;
};

#endif //NEWABYSS_FULLBRIGHT_H