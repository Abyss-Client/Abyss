// class by sleepyfish for abyss recode
// February 2024 Thursday 2:55 AM

#include "GameSettings.h"

GameSettings::GameSettings(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["GameSettings"];
    this->instanceObject = this->getObjectFieldNormal(instance, Mapper::mapper_fields["minecraft_gameSettings"]);
}

jclass GameSettings::getInstanceClass() {
    return this->instanceClass;
}

jobject GameSettings::getInstanceObject() {
    return this->instanceObject;
}

jfloat GameSettings::getFOV() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_fovSetting"]);
}

void GameSettings::setFOV(jfloat value) {
    this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_fovSetting"], value);
}

jfloat GameSettings::getGamma() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_gammaSetting"]);
}

void GameSettings::setGamma(jfloat value) {
    this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_gammaSetting"], value);
}

void GameSettings::setKeybind(const std::string& mappingName, jboolean state) {
    jobject keyObj = this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_keyBind" + mappingName]);
    this->setBooleanField(keyObj, Mapper::mapper_fields["keybinding_pressed"], state);
    this->deleteRef(keyObj);
}

jboolean GameSettings::isKeybindPressed(const std::string &mappingName) {
    jobject keyObj = this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_keyBind" + mappingName]);
    return this->getBooleanField(keyObj, Mapper::mapper_fields["keybinding_pressed"]);
}

jobject GameSettings::getKeybind(const std::string &mappingName) {
    return this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["gameSetting_keyBind" + mappingName]);;
}

jfloat GameSettings::getSensitivity() {
    return 0.5f;
}