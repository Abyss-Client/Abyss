// class by sleepyfish for abyss recode
// February 2024 Tuesday 11:34 PM

#ifndef NEWABYSS_MINECRAFT_H
#define NEWABYSS_MINECRAFT_H

#include "../SdkClass.h"
#include "../../../../../../../libraries/jni/jni.h"

#include "entity/EntityPlayerSP.h"
#include "world/WorldClient.h"
#include "settings/GameSettings.h"
#include "settings/Session.h"
#include "utils/MovingObjectPosition.h"
#include "world/ServerData.h"

struct Minecraft : SdkClass {
    Minecraft();

    jclass getInstanceClass() override;
    jobject getInstanceObject() override;

    EntityPlayerSP* thePlayer;
    WorldClient* theWorld;
    Session* session;
    GameSettings* gameSettings;
    ServerData* serverData;

    Entity getPointedEntity();
    jboolean isSinglePlayer();
    jobject getCurrentScreen();
    MovingObjectPosition getObjectMouseOver();
    jobject getRenderManager();

    jint getDebugFPS();
    void setDebugFPS(jint value);

    void setRightClickDelay(jint value);
    jint getRightClickDelay();

    void setLeftClickDelay(jint value);
    jint getLeftClickDelay();

    bool inGui();

    void unInject();
};

#endif //NEWABYSS_MINECRAFT_H