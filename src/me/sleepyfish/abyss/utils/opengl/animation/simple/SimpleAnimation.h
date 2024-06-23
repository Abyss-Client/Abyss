// class by sleepyfish for abyss recode
/*
 * This class is from Snow Client.
 * Warning : Unauthorized reproduction, skidding, or decompilation of this code is strictly prohibited.
 * Author  : SleepyFish, NextByte 2024
 */

#ifndef NEWABYSS_SIMPLEANIMATION_H
#define NEWABYSS_SIMPLEANIMATION_H

#include <chrono>
#include "AnimationUtils.h"
#include "../normal/Animation.h"

class SimpleAnimation {
private:
    float value;
    long long lastMS;

public:
    SimpleAnimation(float value) :
        value(value),
        lastMS(std::chrono::system_clock::now().time_since_epoch().count())
    {}

    void updateTimer() {
        lastMS = (std::chrono::system_clock::now().time_since_epoch().count());
    }

    void setAnimation(float value, double speed) {
        auto currentMS = std::chrono::system_clock::now().time_since_epoch().count();
        auto delta = currentMS - lastMS;
        lastMS = currentMS;

        double deltaValue = 0.0;

        if (speed > 28)
            speed = 28;

        if (speed != 0.0)
            deltaValue = std::abs(value - this->value) * 0.35f / (10.0 / speed);

        this->value = AnimationUtils::calculateCompensation(value, this->value, deltaValue, delta);
    }

    float getValue() const {
        return value;
    }

    void setValue(float value) {
        this->value = value;
    }
};

#endif //NEWABYSS_SIMPLEANIMATION_H