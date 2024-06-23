// class by sleepyfish for abyss recode
// March 2024 Sunday 4:52 PM

#ifndef NEWABYSS_AUTOTOOL_H
#define NEWABYSS_AUTOTOOL_H

#include "../../Module.h"

class AutoTool : public Module {

public:
    AutoTool();

    void onTick() override;
    void onToggleTail() override;

    const std::vector<String> pickaxeBlocks = {
        "block",
        "stone",
        "cobblestone",
        "glass",
        "obsidian",
        "bricks",
        "andesite",
        "granite",
        "ore"
    };

    const std::vector<String> axeBlocks = {
        "planks",
        "wood",
        "ladder"
    };

    const std::vector<String> shearBlocks = {
        "wool",
        "leaves",
        "vines",
        "pumpkin",
        "melon",
        "web"
    };

    const std::vector<String> weaponNames = {
        "sword",
        "stick",
        "axe"
    };

};

#endif //NEWABYSS_AUTOTOOL_H