// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#ifndef NEWABYSS_ABYSS_H
#define NEWABYSS_ABYSS_H

#include "../utils/Logger.h"
#include "../java/Java.h"
#include "../java/mapper/Mapper.h"
#include "../java/sdk/Sdk.h"
#include "../modules/ModuleManager.h"
#include "../utils/notification/NotificationUtils.h"

class Abyss {

public:
    static inline HMODULE HModule;

    static inline Logger logger;
    static inline Java java;
    static inline Mapper mapper;
    static inline Sdk sdk;
    static inline ModuleManager modManager;
    static inline NotificationUtils notify;

    static inline Minecraft* minecraft;

    static inline bool isInjected;
    static inline bool isDebugging;

    static void inject(HMODULE mod);
    static void unInject();

    static void onTickUpdate();
};

#endif //NEWABYSS_ABYSS_H