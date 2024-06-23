// class by sleepyfish for abyss recode
// March 2024 Saturday 11:10 PM

#ifndef NEWABYSS_DISABLER_H
#define NEWABYSS_DISABLER_H

#include "../../Module.h"

class Disabler : public Module {

public:
    Disabler();

    void onEnableEvent() override;

};

#endif //NEWABYSS_DISABLER_H