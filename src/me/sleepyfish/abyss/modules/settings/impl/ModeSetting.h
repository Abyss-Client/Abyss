// class by sleepyfish for abyss recode
// February 2024 Saturday 11:58 PM

#ifndef NEWABYSS_MODESETTING_H
#define NEWABYSS_MODESETTING_H

#include "../../../utils/type/String.h"
#include "../Setting.h"
#include "../../../utils/type/ArrayList.h"

class ModeSetting : public Setting {

private:
    String curretMode;
    std::vector<String> modes;

public:
    ModeSetting(const String name, const std::vector<String> modes, const String currentMode) :
        Setting(name, 3),
        modes(modes),
        curretMode(currentMode)
    {}

    std::vector<String> getModes() {
        return this->modes;
    }

    void setMode(String mode) {
        this->curretMode = mode;
    }

    String getMode() {
        return this->curretMode;
    }
};

#endif //NEWABYSS_MODESETTING_H