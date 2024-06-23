// class by sleepyfish for abyss recode
// February 2024 Saturday 7:39 AM

#ifndef NEWABYSS_NOTIFICATION_H
#define NEWABYSS_NOTIFICATION_H

#include "../type/String.h"

class Notification {

public:
    String title;
    String message;
    float expireTime;
    ImVec2 shadowPosMin;
    ImVec2 shadowPosMax;

    Notification(const String title, const String message, float duration) :
        title(title),
        message(message),
        expireTime(duration)
    {}

};

#endif //NEWABYSS_NOTIFICATION_H