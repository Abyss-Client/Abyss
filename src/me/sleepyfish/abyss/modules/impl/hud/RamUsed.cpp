// class by sleepyfish for abyss recode
// March 2024 Friday 11:20 PM

#include "RamUsed.h"
#include "../../../utils/MemoryStats.h"

RamUsed::RamUsed() : HudModule("RamUsed", "Renders the Server name on the HUD") {
    this->addSetting(RamUsed::showText);
}

void RamUsed::renderMod() {
    String ram;

    const long freeRam = (long) MemoryStats::freeMemory();
    const long usedRam = (long) MemoryStats::totalMemory() - freeRam;
    const long maxRam  = (long) MemoryStats::maxMemory();

    if (false) {
        if (RamUsed::showText->isEnabled()) {
            ram = (String) "Used Ram: " + std::to_string(MemoryStats::bytesToMb(usedRam));
        } else {
            ram = (String) " " + std::to_string(MemoryStats::bytesToMb(usedRam));
        }
    } else {
        if (RamUsed::showText->isEnabled()) {
            ram = (String) "Free Ram: " + std::to_string(MemoryStats::bytesToMb(maxRam - usedRam));
        } else {
            ram = (String) " " + std::to_string(MemoryStats::bytesToMb(maxRam - usedRam));
        }
    }

    this->text = ram;
}