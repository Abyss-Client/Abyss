// class by sleepyfish for abyss recode
// March 2024 Sunday 5:06 PM

#include "Block.h"
#include "../../../../utils/Utils.h"
#include "../../java/JavaString.h"

Block::Block(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["Block"];
    this->instanceObject = instance;
}

jclass Block::getInstanceClass() {
    return this->instanceClass;
}

jobject Block::getInstanceObject() {
    return this->instanceObject;
}

String Block::getLocalizedName() {
    if (this->isNull())
        return "instance is null";

    JavaString str = JavaString(this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["getLocalizedName"]));
    if (str.isNull())
        return "string instance is null";

    return str.toString();
}

jboolean Block::isAirBlock() {
    return Utils::instanceOf(this->getInstanceObject(), Mapper::mapper_classes["BlockAir"]);
}