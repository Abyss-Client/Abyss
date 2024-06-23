// class by sleepyfish for abyss recode
// February 2024 Monday 2:45 PM

#ifndef NEWABYSS_TEXTSETTING_H
#define NEWABYSS_TEXTSETTING_H

#include "../Setting.h"

class TextSetting : public Setting {
public:
    String text;

    TextSetting(const String& name, String text) :
            Setting(name, 5),
            text(text)
    {}

    TextSetting(const String& name, const String& desc, String text) :
            Setting(name, desc, 5),
            text(text)
    {}

};

#endif //NEWABYSS_TEXTSETTING_H