// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#include "Abyss.h"
#include "thread"
#include "../utils/Utils.h"
#include "../../../../../libraries/minhook/minhook.h"

// injection call
void Abyss::inject(HMODULE instance) {
    if (!Abyss::isInjected) {
        Abyss::HModule = instance;

        Abyss::logger.inject();
        Abyss::java.inject();
        Abyss::mapper.inject();
        Abyss::sdk.inject();
        Abyss::modManager.inject();

        MH_Initialize();
        ClickGui::inject();
        Abyss::notify.inject();

        const bool f = 1;
        const String name = Abyss::minecraft->session->getUsername().toLowercase();
        if ( (name.equals("sleepyfish_yt") || name.equals("nickthetrick321")) && f) {
            Abyss::logger.log("| Abyss - Info: ImGui Debug Window Enabled");
            Abyss::logger.log("| Abyss - Info: Showing Console Enabled");
            Abyss::logger.nextLine();

            Abyss::isDebugging = true;
        }

        if (!Abyss::isDebugging && f)
            Abyss::logger.hide();

        Utils::callGarbageCollector();
        Abyss::isInjected = true;

        Abyss::logger.nextLine();
        Abyss::logger.log("============================== Inject Done ==============================");
        Abyss::logger.nextLine();

        ClickGui::draw = true;
    } else Abyss::logger.log("| Abyss - Err: Abyss is already Injected");
}

// un injection call
void Abyss::unInject() {
    ClickGui::draw = false;

    ClickGui::unInject();
    Abyss::notify.unInject();
    MH_Uninitialize();

    Abyss::modManager.unInject();
    Abyss::sdk.unInject();
    Abyss::mapper.unInject();
    Abyss::java.unInject();
    Abyss::logger.unInject();

    FreeLibrary(Abyss::HModule);
}

// while loop call
void Abyss::onTickUpdate() {
    if (Abyss::minecraft->isNull())
        return;

    if (Abyss::minecraft->thePlayer->isNull())
        return;

    if (Abyss::minecraft->theWorld->isNull())
        return;

    Abyss::modManager.onModuleTick();
}