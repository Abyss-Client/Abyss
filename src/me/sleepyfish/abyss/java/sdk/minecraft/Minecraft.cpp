// class by sleepyfish for abyss recode
// February 2024 Tuesday 11:34 PM

#include "Minecraft.h"
#include "world/ServerData.h"

Minecraft::Minecraft() {
    this->instanceClass = Mapper::mapper_classes["Minecraft"];

    if (Mapper::currentMapping == Mapper::Mappings::Lunar) {
        this->instanceObject = this->getStaticObjectFieldNormal(this->instanceClass, Mapper::mapper_fields["minecraft_theMinecraft"]);
    } else {
        this->instanceObject = this->getStaticMethodObject(this->instanceClass, Mapper::mapper_voids["minecraft_getMinecraft"]);
    }

    if (!this->isNull()) {
        this->session = new Session(this->instanceObject);
        this->session->checkForName();

        this->gameSettings = new GameSettings(this->instanceObject);

        this->thePlayer = new EntityPlayerSP(this->instanceObject);
        this->serverData = new ServerData(this->instanceObject);

        // crash here on lunar
        this->theWorld = new WorldClient(this->instanceObject);
    }
}

void Minecraft::unInject() {
    this->deleteRef(this->thePlayer->instanceObject);
    this->deleteRef(this->thePlayer->instanceClass);
    this->thePlayer = nullptr;

    this->deleteRef(this->theWorld->instanceObject);
    this->deleteRef(this->theWorld->instanceClass);
    this->theWorld = nullptr;

    this->deleteRef(this->gameSettings->instanceObject);
    this->deleteRef(this->gameSettings->instanceClass);
    this->gameSettings = nullptr;

    this->deleteRef(this->session->instanceObject);
    this->deleteRef(this->session->instanceClass);
    this->session = nullptr;

    this->deleteRef(this->instanceObject);
    this->deleteRef(this->instanceClass);
}

jclass Minecraft::getInstanceClass() {
    return this->instanceClass;
}

jobject Minecraft::getInstanceObject() {
    return this->instanceObject;
}

bool Minecraft::inGui() {
    return this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["minecraft_currentScreen"]) != nullptr;
}

Entity Minecraft::getPointedEntity() {
    return {
        this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["minecraft_pointedEntity"])
    };
}

jboolean Minecraft::isSinglePlayer() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["minecraft_isSingleplayer"]);
}

jobject Minecraft::getCurrentScreen() {
    return this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["minecraft_currentScreen"]);
}

MovingObjectPosition Minecraft::getObjectMouseOver() {
    return {
        this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["minecraft_objectMouseOver"])
    };
}

jobject Minecraft::getRenderManager() {
    return this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["minecraft_renderManager"]);
}

jint Minecraft::getDebugFPS() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["minecraft_debugFPS"]);
}

void Minecraft::setDebugFPS(jint value) {
    this->setIntField(this->getInstanceObject(), Mapper::mapper_fields["minecraft_debugFPS"], value);
}

void Minecraft::setRightClickDelay(jint value) {
    this->setIntField(this->getInstanceObject(), Mapper::mapper_fields["minecraft_rightClickDelayTimer"], value);
}

jint Minecraft::getRightClickDelay() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["minecraft_rightClickDelayTimer"]);
}

void Minecraft::setLeftClickDelay(jint value) {
    this->setIntField(this->getInstanceObject(), Mapper::mapper_fields["minecraft_leftClickCounter"], value);
}

jint Minecraft::getLeftClickDelay() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["minecraft_leftClickCounter"]);
}