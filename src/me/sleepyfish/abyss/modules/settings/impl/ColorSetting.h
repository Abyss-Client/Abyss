// class by sleepyfish for abyss recode
// February 2024 Friday 1:57 AM

#ifndef NEWABYSS_COLORSETTING_H
#define NEWABYSS_COLORSETTING_H

#include "../Setting.h"
#include "../../../../../../../libraries/imgui/imgui.h"

class ColorSetting : public Setting {

private:
    ImVec4 color;
    bool renderName;

public:
    ColorSetting(const String name, ImVec4 color, const bool renderName) :
            Setting(name, 4),
            color(color),
            renderName(renderName)
    {}

    ColorSetting(const String name, const String desc, ImVec4 color, const bool renderName) :
            Setting(name, desc, 4),
            color(color),
            renderName(renderName)
    {}

    ImVec4 getColor() {
        return this->color;
    }

    void setColor(ImVec4 color) {
        this->color = color;
    }

    bool shouldRenderName() {
        return this->renderName;
    }

};

#endif //NEWABYSS_COLORSETTING_H