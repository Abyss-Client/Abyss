// class by sleepyfish for abyss recode
// February 2024 Friday 8:43 AM

#include "Sdk.h"
#include "../../client/Abyss.h"

void Sdk::inject() {
    if (Sdk::isNull) {
        Abyss::logger.nextLine();
        Abyss::logger.log("/ SDK - Info: Inject");
        Abyss::minecraft = new Minecraft();
        Abyss::logger.log("\\ SDK - Info: Inject Done");
        Abyss::logger.nextLine();
        Sdk::isNull = false;
    }
}

void Sdk::unInject() {
    if (!Sdk::isNull) {
        Abyss::logger.nextLine();
        Abyss::logger.log("/ SDK - Info: UnInject");
        Abyss::minecraft->unInject();
        Abyss::logger.log("\\ SDK - Info: UnInject Done");
        Abyss::logger.nextLine();
        Sdk::isNull = true;
    }
}