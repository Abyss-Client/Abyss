// class by sleepyfish for abyss recode
// March 2024 Friday 11:20 PM

#include "ServerName.h"
#include "../../../client/Abyss.h"

ServerName::ServerName() : HudModule("Server Name", "Renders the Server name on the HUD") {
    this->addSetting(ServerName::showText);
}

void ServerName::renderMod() {
    String text = "null";

    if (Abyss::minecraft->theWorld->isNull()) {
        this->text = "             ";
        return;
    }

    text = Abyss::minecraft->serverData->getServerName();

    if (ServerName::showText->isEnabled()) {
        text = (String) "Name: " + text;
    }

    this->text = text;
}