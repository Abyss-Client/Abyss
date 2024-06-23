// class by sleepyfish for abyss recode
// March 2024 Wednesday 6:45 PM

#ifndef NEWABYSS_TIMECHANGER_H
#define NEWABYSS_TIMECHANGER_H

#include "../../Module.h"
#include "../../settings/impl/ModeSetting.h"

class TimeChanger : public Module {

public:
    TimeChanger();

    void onEnableEvent() override;
    void onTick() override;

    const std::vector<String> TimeModes {
        "Dawn", "Morning", "Noon", "Afternoon", "Evening", "Dusk", "Night", "Midnight"
    };

    ModeSetting* timeMode = new ModeSetting("Mode", TimeModes, "Night");
};

#endif //NEWABYSS_TIMECHANGER_H