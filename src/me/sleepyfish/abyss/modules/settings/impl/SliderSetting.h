// class by sleepyfish for abyss recode
// February 2024 Thursday 10:16 PM

#ifndef NEWABYSS_SLIDERSETTING_H
#define NEWABYSS_SLIDERSETTING_H

#include "../Setting.h"

class SliderSetting : public Setting {

private:
    const int minVal;
    const int maxVal;

public:
    int currVal;
    bool shouldFormat = false;

    SliderSetting(const String name, int currVal, const int minVal, const int maxVal) :
            Setting(name, "-", 2),
            currVal(currVal),
            minVal(minVal),
            maxVal(maxVal)
    {}

    SliderSetting(const String name, const String desc, int currVal, const int minVal, const int maxVal) :
            Setting(name, desc, 2),
            currVal(currVal),
            minVal(minVal),
            maxVal(maxVal)
    {}

    int getValue() {
        return this->currVal;
    }

    int getMinValue() const {
        return this->minVal;
    }

    int getMaxValue() const {
        return this->maxVal;
    }
};

#endif //NEWABYSS_SLIDERSETTING_H