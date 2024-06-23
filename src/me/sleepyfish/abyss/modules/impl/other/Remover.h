// class by sleepyfish for abyss recode
// March 2024 Monday 7:02 PM

#ifndef NEWABYSS_REMOVER_H
#define NEWABYSS_REMOVER_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"

class Remover : public Module {

public:
    Remover();

    void onTick() override;

    void removeLeftDelay() const;
    void removeRightDelay() const;

    BoolSetting* removeLeft = new BoolSetting("Remove Left", "Also called 'Hit Delay Remover'", true);
    BoolSetting* weaponOnly = new BoolSetting("Weapon Only", "Only works when holding a weapon", true);
    // Space Setting ---
    BoolSetting* removeRight = new BoolSetting("Remove Right", "Also called 'Fast Place'", false);
    BoolSetting* blockOnly = new BoolSetting("Blocks Only", "Only works when holding a block", true);
    BoolSetting* lookingOnly = new BoolSetting("Looking Only", "Only works when looking at a block", false);
};

#endif //NEWABYSS_REMOVER_H