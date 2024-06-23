// class by sleepyfish for abyss recode
// February 2024 Thursday 2:47 AM

#include "World.h"

World::World(jobject instance) {
    this->instanceClass = Mapper::mapper_classes["World"];
    this->instanceObject = this->getObjectField(this->instanceClass, "minecraft_theWorld", instance);
}

jclass World::getInstanceClass() {
    return this->instanceClass;
}

jobject World::getInstanceObject() {
    return this->instanceObject;
}

String World::getName() {
    return "null";
}

jboolean World::isAirBlock(jdouble x, jdouble y, jdouble z) {

    // This crashes thank me later for telling
    jclass blockPosClass = Mapper::mapper_classes["BlockPos"];
    jmethodID blockPosConstructor = this->getVoid(blockPosClass, "<init>", "(DDD)V");
    jobject blockpos = this->newObject(blockPosClass, blockPosConstructor, x, y, z);
    blockPosConstructor = nullptr;
    this->deleteRef(blockPosClass);

    return this->getBooleanMethodArgs(this->getInstanceObject(), Mapper::mapper_voids["world_isAirBlock"], blockpos);
}

JavaList World::getEntities() {
    return {
        this->getObjectFieldNormal(this->instanceObject, Mapper::mapper_fields["world_playerEntities"])
    };
}

ArrayList<EntityPlayer> World::getPlayerList() {
    jobject playerEntitiesObj = this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["world_playerEntities"]);
    auto playerEntitiesList = JavaList(playerEntitiesObj);
    jobjectArray playerEntities = playerEntitiesList.toArray();

    const int size = EnvUtils::Env->GetArrayLength(playerEntities);
    ArrayList<EntityPlayer> finalList;

    for (int i = 0; i < size; i++) {
        jobject obj_player = this->getItemInArray(playerEntities, i);
        if (!obj_player) continue;

        auto player = EntityPlayer(obj_player);
        if (!player.isNull())
            finalList.add(player);
    }

    this->deleteRef(playerEntitiesObj);
    this->deleteRef(playerEntities);

    return finalList;
}

/*
ArrayList<EntityPlayer> World::getEntities() {
    ArrayList<EntityPlayer> list;

    jobject getLoadedEntityList = this->getObjectFieldNormal(this->getInstanceObject(), Mapper::mapper_fields["world_playerEntities"]);
    if (getLoadedEntityList == nullptr)
        return list;

    auto* playerEntitiesList = new JavaList(getLoadedEntityList);
    if (playerEntitiesList->isNull())
        return list;

    jobjectArray playerEntities = playerEntitiesList->toArray();
    if (playerEntities == nullptr)
        return list;

    jsize size = EnvUtils::Env->GetArrayLength(playerEntities);

    for (int i = 0; i < size; i++) {
        jobject obj_player = EnvUtils::Env->GetObjectArrayElement(playerEntities, i);
        if (!obj_player) continue;

        auto player = EntityPlayer(obj_player);
        if (!player.isNull())
            if (!EnvUtils::Env->IsSameObject(Abyss::minecraft->thePlayer->getInstanceObject(), player.getInstanceObject()))
                list.add(player);
    }

    this->deleteRef(getLoadedEntityList);
    this->deleteRef(playerEntities);

    return list;
}
 */