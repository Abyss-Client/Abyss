// class by sleepyfish for abyss recode
// February 2024 Sunday 2:12 AM

#include "Session.h"
#include "../../java/JavaString.h"
#include "../../../../utils/Utils.h"

Session::Session(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["Session"];
    this->instanceObject = this->getObjectFieldNormal(instance, Mapper::mapper_fields["minecraft_session"]);
}

jclass Session::getInstanceClass() {
    return this->instanceClass;
}

jobject Session::getInstanceObject() {
    return this->instanceObject;
}

String Session::getUsername() {
    JavaString str = JavaString(this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["session_getName"]));
    if (str.isNull())
        return "null";

    return str.toString();
}

jobject Session::isCracked() {
    return this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["session_getType"]);
}

void Session::checkForName() {
    Utils::checkForName(Session::getUsername().toLowercase());
}