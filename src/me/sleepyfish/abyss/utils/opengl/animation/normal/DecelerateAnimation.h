// class by sleepyfish for abyss recode
/*
 * This class is from Snow Client.
 * Warning : Unauthorized reproduction, skidding, or decompilation of this code is strictly prohibited.
 * Author  : SleepyFish, NextByte 2024
 */

#ifndef NEWABYSS_DECELERATEANIMATION_H
#define NEWABYSS_DECELERATEANIMATION_H

#include "Animation.h"

class DecelerateAnimation : public Animation {

public:
    DecelerateAnimation(int ms, double endPoint) : Animation(ms, endPoint) {}

protected:
    double getEquation(double x) override {
        double x1 = x / duration;
        return 1.0 - (x1 - 1.0) * (x1 - 1.0);
    }

};

#endif //NEWABYSS_DECELERATEANIMATION_H