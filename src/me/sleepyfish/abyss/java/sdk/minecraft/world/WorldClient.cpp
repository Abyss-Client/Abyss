// class by sleepyfish for abyss recode
// February 2024 Thursday 2:47 AM

#include "WorldClient.h"

WorldClient::WorldClient(jobject instance) : World(instance) {
    this->instanceClass = Mapper::mapper_classes["WorldClient"];
    this->instanceObject = this->getObjectField(this->instanceClass, "minecraft_theWorld", instance);
}

jclass WorldClient::getInstanceClass() {
    return this->instanceClass;
}

jobject WorldClient::getInstanceObject() {
    return this->instanceObject;
}

void WorldClient::sendQuittingDisconnectingPacket() {
    // Crashing in vanilla, thank me later
    this->callVoid(this->getInstanceObject(), Mapper::mapper_voids["worldClient_sendQuittingDisconnectingPacket"]);
}

void WorldClient::setWorldTime(jlong value) {
    this->callLongMethod(this->getInstanceObject(), Mapper::mapper_voids["world_setWorldTime"], value);
}