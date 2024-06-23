// class by sleepyfish for abyss recode
// February 2024 Saturday 6:29 AM

#ifndef NEWABYSS_OVERLAY_H
#define NEWABYSS_OVERLAY_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"

class Overlay : public Module {

public:
    Overlay();

    void onRenderTick() override;

    BoolSetting* renderName = new BoolSetting("Render Name", "Render the name of this client", true);
    BoolSetting* renderIcon = new BoolSetting("Render Icon", "Render the icon of this client", true);
    BoolSetting* renderFps = new BoolSetting("Render FPS", "Render FPS", true);
};

#endif //NEWABYSS_OVERLAY_H