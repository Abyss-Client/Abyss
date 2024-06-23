// class by sleepyfish for abyss recode
// February 2024 Tuesday 8:20 PM

#include "Team.h"

Team::Team(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["Team"];
    this->instanceObject = instance;
}

jclass Team::getInstanceClass() {
    return this->instanceClass;
}

jobject Team::getInstanceObject() {
    return this->instanceObject;
}