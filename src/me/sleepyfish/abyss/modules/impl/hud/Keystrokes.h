// class by sleepyfish for abyss recode
// March 2024 Thursday 11:50 PM

#ifndef NEWABYSS_KEYSTROKES_H
#define NEWABYSS_KEYSTROKES_H

#include "../../HudModule.h"
#include "../../../utils/opengl/animation/simple/SimpleAnimation.h"
#include "../../settings/impl/SliderSetting.h"

class Keystrokes : public HudModule {

public:
    Keystrokes();

    void renderMod() override;

    SliderSetting* boxSize = new SliderSetting("Key size", "Also called 'Key scale'", 48, 20, 200);
    SliderSetting* boxGap = new SliderSetting("Key Gap", "Also called 'Key Spacing'", 2, 0, 20);

    SimpleAnimation* wAnimation;
    SimpleAnimation* sAnimation;
    SimpleAnimation* aAnimation;
    SimpleAnimation* dAnimation;
    SimpleAnimation* spaceAnimation;

    ImVec4 getColor(int key, SimpleAnimation *ani);
};

#endif //NEWABYSS_KEYSTROKES_H