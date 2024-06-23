// class by sleepyfish for abyss recode
/*
 * This class is from Snow Client.
 * Warning : Unauthorized reproduction, skidding, or decompilation of this code is strictly prohibited.
 * Author  : SleepyFish, NextByte 2024
 */

#ifndef NEWABYSS_ANIMATIONUTILS_H
#define NEWABYSS_ANIMATIONUTILS_H

#include "../normal/DecelerateAnimation.h"

class AnimationUtils {

public:
    static DecelerateAnimation getAnimation() {
        return {
            450, 1.0
        };
    }

    static float calculateCompensation(const float target, float current, const double speed, const long delta) {
        const float diff = current - target;
        const double add = delta * (speed / 50.0);

        if (diff > speed) {
            if (current - add > target) {
                current -= add;
            } else {
                current = target;
            }
        } else if (diff < -speed) {
            if (current + add < target) {
                current += add;
            } else {
                current = target;
            }
        } else {
            current = target;
        }

        return current;
    }
};

#endif //NEWABYSS_ANIMATIONUTILS_H