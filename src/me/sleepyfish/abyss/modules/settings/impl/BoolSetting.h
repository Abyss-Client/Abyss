// class by sleepyfish for abyss recode
// February 2024 Saturday 10:48 PM

#ifndef NEWABYSS_BOOLEANSETTING_H
#define NEWABYSS_BOOLEANSETTING_H

#include <functional>
#include "../Setting.h"

class BoolSetting : public Setting {

public:
    bool enabled;

    BoolSetting(const String name, bool enabled) :
            Setting(name, 1),
            enabled(enabled)
    {}

    BoolSetting(const String name, const String desc, bool enabled) :
            Setting(name, desc, 1),
            enabled(enabled)
    {}

    bool isEnabled() {
        return this->enabled;
    }

    void toggle() {
        this->enabled = !this->enabled;
        this->onToggleEvent();
    }

    std::function<void()> onToggleEvent = []() {};

};

#endif //NEWABYSS_BOOLEANSETTING_H