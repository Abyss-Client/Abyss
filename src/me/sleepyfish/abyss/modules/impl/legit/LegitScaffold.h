// class by sleepyfish for abyss recode
// February 2024 Wednesday 2:48 PM

#ifndef NEWABYSS_LEGITSCAFFOLD_H
#define NEWABYSS_LEGITSCAFFOLD_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"

class LegitScaffold : public Module {

public:
    LegitScaffold();

    void onTick() override;

    void setSneak(jboolean state);

    BoolSetting* blockOnly  = new BoolSetting("Blocks Only", "Only works when holding a block", true);
    BoolSetting* lookingOnly = new BoolSetting("Looking Only", "Only works when looking at a block", true);
    BoolSetting* onlyHolding   = new BoolSetting("Hold Only", "Only works when holding", true);
    BoolSetting* onlyLookingDown = new BoolSetting("Only Looking Down", "Only works when looking down", true);

};

#endif //NEWABYSS_LEGITSCAFFOLD_H