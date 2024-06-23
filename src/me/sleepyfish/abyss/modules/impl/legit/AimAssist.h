// class by sleepyfish for abyss recode
// March 2024 Monday 11:37 PM

#ifndef NEWABYSS_AIMASSIST_H
#define NEWABYSS_AIMASSIST_H

#include "../../Module.h"
#include "../../settings/impl/BoolSetting.h"
#include "../../settings/impl/SliderSetting.h"
#include "../../settings/impl/ModeSetting.h"

class AimAssist : public Module {

public:
    AimAssist();

    void onTick() override;

    Vector2 getRotations(const EntityPlayer entity);
    EntityPlayer getTarget();

    const std::vector<String> AimModes {
        "Smooth", "Smok", "Blatant", "Dont hit Me"
    };

    ModeSetting* aimMode = new ModeSetting("Mode", AimModes, "Smooth");
    SliderSetting* range = new SliderSetting("Range", "Also called 'Reach'", 4, 1, 6);
    SliderSetting* fovRange = new SliderSetting("Max Angle", "Also called 'Fov'", 65, 15, 360);
    BoolSetting* weaponOnly = new BoolSetting("Weapon Only", "Only works when holding a weapon", true);
    BoolSetting* multiPoint = new BoolSetting("Multipoint", "Only works when not looking at a player", false);
    // space setting
    BoolSetting* increaseStrafe = new BoolSetting("Increase Strafe", "Increases aim speed while strafing", false);
    SliderSetting* aimOffset = new SliderSetting("Aim Offset", "Adds Value to the rotation", 0, 0, 10);
    BoolSetting* prediction = new BoolSetting("Prediction", "Adds value when strafing", true);
    SliderSetting* predictVal = new SliderSetting("Predict Value", "The value that gets added when strafing", 4, 1, 20);
    // space setting
    SliderSetting* speedYaw = new SliderSetting("Yaw Speed", "Also called 'Horizontal Speed'", 20, 1, 100);
    SliderSetting* speedPitch = new SliderSetting("Pitch Speed", "Also called 'Vertical Speed'", 20, 1, 100);
    SliderSetting* assistDelay = new SliderSetting("Assist Delay", "Ticks it should wait before Aiming", 0, 0, 1000);
    // space setting
    BoolSetting* ignoreFriends = new BoolSetting("Ignore Friends", "Ignore your Team and added friends", true);
    BoolSetting* ignoreInvis = new BoolSetting("Ignore Invis", "Ignore invisible players", true);
    BoolSetting* ignoreBots = new BoolSetting("Ignore Bots", "Ignore bots", true);

};

#endif //NEWABYSS_AIMASSIST_H