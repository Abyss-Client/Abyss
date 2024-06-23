// class by sleepyfish for abyss recode
/*
 * This class is from Snow Client.
 * Warning : Unauthorized reproduction, skidding, or decompilation of this code is strictly prohibited.
 * Author  : SleepyFish, NextByte 2024
 */

#ifndef NEWABYSS_ANIMATION_H
#define NEWABYSS_ANIMATION_H

#include <chrono>
#include "../../../MathUtils.h"

class Timer {
private:
    std::chrono::steady_clock::time_point start;

public:
    Timer() {
        reset();
    }

    void reset() {
        start = std::chrono::steady_clock::now();
    }

    bool delay(int milliseconds) {
        auto elapsed = std::chrono::steady_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() >= milliseconds;
    }

    long getTime() const {
        auto elapsed = std::chrono::steady_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    void setTime(long milliseconds) {
        start = std::chrono::steady_clock::now() - std::chrono::milliseconds(milliseconds);
    }
};

class Animation {

    enum class AnimationDirection { FORWARDS, BACKWARDS };

protected:
    Timer timer;
    int duration;
    double endPoint;
    AnimationDirection direction;

public:
    Animation(int duration, double endPoint) : duration(duration), endPoint(endPoint), direction(AnimationDirection::FORWARDS) {}

    Animation(int ms, double endPoint, AnimationDirection direction) : duration(ms), endPoint(endPoint), direction(direction) {}

    virtual ~Animation() {}

    bool isDone(AnimationDirection dir) {
        return isDone() && direction == dir;
    }

    double getLinearOutput() {
        return 1.0 - static_cast<double>(timer.getTime()) / duration * endPoint;
    }

    void reset() {
        timer.reset();
    }

    bool isDone() {
        return timer.delay(duration);
    }

    double getValue() {
        if (this->direction == AnimationDirection::FORWARDS) {
            return this->isDone() ? this->endPoint : this->getEquation((double) this->timer.getTime()) * this->endPoint;
        } else if (this->isDone()) {
            return 0.0f;
        } else {
            return (1.0f - this->getEquation((double) this->timer.getTime())) * this->endPoint;
        }
    }

    virtual double getEquation(double var1) = 0;

    float getValueF() {
        return static_cast<float>(getValue());
    }

    void setValue(double value) {
        endPoint = value;
    }

    void setDirection(AnimationDirection dir) {
        if (direction != dir) {
            direction = dir;
            timer.setTime(std::chrono::steady_clock::now().time_since_epoch().count() - (duration - MathUtils::min_int(duration, (int) timer.getTime())));
        }
    }

    void changeDirection() {
        setDirection((direction == AnimationDirection::FORWARDS) ? AnimationDirection::BACKWARDS : AnimationDirection::FORWARDS);
    }

    double getEndPoint() const {
        return endPoint;
    }

    void setEndPoint(double ep) {
        endPoint = ep;
    }

    int getDuration() const {
        return duration;
    }

    void setDuration(int dur) {
        duration = dur;
    }

    AnimationDirection getDirection() const {
        return direction;
    }
};

#endif //NEWABYSS_ANIMATION_H