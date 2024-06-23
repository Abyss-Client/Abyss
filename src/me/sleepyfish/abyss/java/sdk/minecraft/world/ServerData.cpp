// class by sleepyfish for abyss recode
// March 2024 Friday 11:22 PM

#include "ServerData.h"
#include "../../java/JavaString.h"

ServerData::ServerData(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["ServerData"];
    this->instanceObject = this->getObjectFieldNormal(instance, Mapper::mapper_fields["minecraft_currentServerData"]);
}

jclass ServerData::getInstanceClass() {
    return this->instanceClass;
}

jobject ServerData::getInstanceObject() {
    return this->instanceObject;
}

String ServerData::getServerIP() {
    if (this->isNull())
        return "null";

    JavaString str = JavaString(this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["serverData_serverIP"]));
    if (str.isNull())
        return "null";

    return str.toString();
}

String ServerData::getServerName() {
    if (this->isNull())
        return "null";

    JavaString str = JavaString(this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["serverData_serverName"]));
    if (str.isNull())
        return "null";

    return str.toString();
}