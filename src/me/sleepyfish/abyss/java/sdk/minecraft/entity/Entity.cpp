// class by sleepyfish for abyss recode
// February 2024 Thursday 2:13 AM

#include "Entity.h"
#include "../../java/JavaString.h"

Entity::Entity() {
    this->instanceClass = Mapper::mapper_classes["Entity"];
    this->instanceObject = nullptr;
}

Entity::Entity(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["Entity"];
    this->instanceObject = instance;
}

jclass Entity::getInstanceClass() {
    return instanceClass;
}

jobject Entity::getInstanceObject() {
    return this->instanceObject;
}

jboolean Entity::isDead() {
    return this->getBooleanField(this->getInstanceObject(), Mapper::mapper_fields["entity_isDead"]);
}

jboolean Entity::isSneaking() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entity_isSneaking"]);
}

void Entity::setSneaking(const jboolean state) {
    this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entity_setSneaking"], state);
}

jboolean Entity::inWater() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entity_inWater"]);
}

jboolean Entity::isInvisible() {
    return this->getBooleanMethod(this->getInstanceObject(), Mapper::mapper_voids["entity_isInvisible"]);
}

jfloat Entity::getWidth() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_width"]);
}

jfloat Entity::getHeight() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_height"]);
}

Vector3 Entity::getPosition() {
    if (this->isNull())
        return {0, 0, 0};

    return {
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_posX"]),
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_posY"]),
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_posZ"])
    };
}

Vector3 Entity::getLastPosition() {
    if (this->isNull())
        return {0, 0, 0};

    return {
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_lastTickPosX"]),
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_lastTickPosY"]),
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_lastTickPosZ"])
    };
}

Vector3 Entity::getEyePosition() {
    if (this->isNull())
        return {0, 0, 0};

    const Vector3 pos = getPosition();

    return {
        (jfloat) pos.x,
        (jfloat) pos.y + (this->getHeight() * 0.85F),
        (jfloat) pos.z
    };
}

Vector3 Entity::getMotion() {
    if (this->isNull())
        return {0, 0, 0};

    return {
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_motionX"]),
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_motionY"]),
        (jfloat) this->getDoubleField(this->getInstanceObject(), Mapper::mapper_fields["entity_motionZ"])
    };
}

jboolean Entity::onGround() {
    return this->getBooleanField(this->getInstanceObject(), Mapper::mapper_fields["entity_onGround"]);
}

String Entity::getName() {
    JavaString str = JavaString(this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["entity_getName"]));
    if (str.isNull())
        return "null";

    return str.toString();
}

Vector2 Entity::getRotation() {
    return {
        this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_rotationYaw"]),
        this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_rotationPitch"])
    };
}

void Entity::setRotation(const Vector2 vec, bool save) {
    if (save) {
        if (abs(vec.x) <= 10000 && vec.x != -1)
            this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_rotationYaw"], vec.x);

        if (abs(vec.y) <= 90 && vec.y != -1)
            this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_rotationPitch"], vec.y);
    } else {
        this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_rotationYaw"], vec.x);
        this->setFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_rotationPitch"], vec.y);
    }
}

jint Entity::getTicksExisted() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["entity_ticksExisted"]);
}

jfloat Entity::getFallDistance() {
    return this->getFloatField(this->getInstanceObject(), Mapper::mapper_fields["entity_fallDistance"]);
}

JavaUUID Entity::getUUID() {
    return {
        this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["entity_getUUID"])
    };
}

jint Entity::getHurtResistantTime() {
    return this->getIntField(this->getInstanceObject(), Mapper::mapper_fields["entity_hurtResistantTime"]);
}

Team Entity::getTeam() {
    return {
        this->getObjectMethod(this->getInstanceObject(), Mapper::mapper_voids["entityLivingBase_getTeam"])
    };
}