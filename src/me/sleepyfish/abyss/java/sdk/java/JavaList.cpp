#include "JavaList.h"

JavaList::JavaList(jobject instance) {
	this->instanceClass = Mapper::mapper_classes["JavaList"];
	this->instanceObject = instance;
}

jclass JavaList::getInstanceClass() {
    return this->instanceClass;
}

jobject JavaList::getInstanceObject() {
    return this->instanceObject;
}

jobjectArray JavaList::toArray() {
	if (this->isNull())
		return nullptr;

	return (jobjectArray) this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["list_toArray"]);
}