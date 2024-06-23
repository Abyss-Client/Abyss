// class by sleepyfish for abyss recode
// March 2024 Friday 11:20 PM

#include "ServerIp.h"
#include "../../../client/Abyss.h"

ServerIP::ServerIP() : HudModule("Server IP", "Renders the Server ip on the HUD") {
    this->addSetting(ServerIP::showText);
}

void ServerIP::renderMod() {
    String text;

    if (Abyss::minecraft->theWorld->isNull()) {
        this->text = "             ";
        return;
    }

    text = Abyss::minecraft->serverData->getServerIP();

    if (ServerIP::showText->isEnabled()) {
        text = (String) "IP: " + text;
    }

    this->text = text;
}