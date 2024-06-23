// class by sleepyfish for abyss recode
// February 2024 Wednesday 3:41 PM

#include <sstream>
#include "CustomScript.h"
#include "../../../gui/ClickGui.h"
#include "../../../client/Abyss.h"

CustomScript::CustomScript() : Module("Custom Script", Category::Other, "Enter ur code") {

}

/**
 * This is a horrible way of doing this
 */
void CustomScript::onTick() {
    if (lines.empty())
        return;

    this->ignoreGuiState = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string &current_line = lines[i];
        if (i == 1 && current_line == "#ignoreGui") {
            this->ignoreGuiState = true;
            continue;
        }

        if (i == 2)
            continue;

        if (current_line.empty())
            break;

        size_t openParenIndex = current_line.find('(');
        if (openParenIndex != std::string::npos) {
            std::string command = current_line.substr(0, openParenIndex);
            std::vector<std::string> arguments = extractArguments(current_line);

            if (command == "abyss.detach") {
                Abyss::isInjected = false;
                return;
            }

            if (command == "abyss.clearRam") {
                Abyss::java.callGarbageCollector();
            }

            if (command == "abyss.notify") {
                std::string check;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> check;

                    Sleep(2000L);
                    Abyss::notify.notify(check);
                }
            }

            if (command == "abyss.message") {
                std::string check;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> check;

                    ClientUtils::messageBox(check);
                }
            }

            if (command.starts_with("module.toggle")) {
                std::string modName;
                bool state;
                if (arguments.size() == 2) {
                    std::istringstream(arguments[0]) >> modName;
                    std::istringstream(arguments[1]) >> state;

                    for (Module *mod: Abyss::modManager.getModules().getVector()) {
                        if (mod->getName().toLowercase().toString() == modName)
                            mod->setToggle(state);
                    }
                }
            }

            if (command == "player.rotate") {
                float rot1, rot2;
                if (arguments.size() == 2) {
                    std::istringstream(arguments[0]) >> rot1;
                    std::istringstream(arguments[1]) >> rot2;

                    Abyss::minecraft->thePlayer->setRotation(Vector2(rot1, rot2));
                }
            }

            if (command == "player.jump") {
                bool check;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> check;

                    if (check && !Abyss::minecraft->thePlayer->onGround())
                        return;

                    Abyss::minecraft->thePlayer->jump();
                }
            }

            if (command == "player.sneak") {
                bool state;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> state;
                    Abyss::minecraft->gameSettings->setKeybind("Sneak", state);
                }
            }

            if (command == "player.forward") {
                bool state;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> state;
                    Abyss::minecraft->gameSettings->setKeybind("Forward", state);
                }
            }

            if (command == "player.backward") {
                bool state;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> state;
                    Abyss::minecraft->gameSettings->setKeybind("Back", state);
                }
            }

            if (command == "player.right") {
                bool state;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> state;
                    Abyss::minecraft->gameSettings->setKeybind("Right", state);
                }
            }

            if (command == "player.left") {
                bool state;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> state;
                    Abyss::minecraft->gameSettings->setKeybind("Left", state);
                }
            }

            if (command == "player.headRotate") {
                float rot1;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> rot1;
                    Abyss::minecraft->thePlayer->setHeadRotations(rot1);
                }
            }

            if (command == "world.isAir") {
                float rot1, rot2, rot3;
                if (arguments.size() == 3) {
                    std::istringstream(arguments[0]) >> rot1;
                    std::istringstream(arguments[1]) >> rot2;
                    std::istringstream(arguments[2]) >> rot3;

                    // jboolean state = Abyss::minecraft->theWorld->isAirBlock(rot1, rot2, rot3);
                }
            }

            if (command == "world.leave") {
                Abyss::minecraft->theWorld->sendQuittingDisconnectingPacket();
            }

            if (command == "world.setTime") {
                long value1;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> value1;
                    Abyss::minecraft->theWorld->setWorldTime(value1);
                }
            }

            if (command == "setting.setFov") {
                float rot1;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> rot1;
                    Abyss::minecraft->gameSettings->setFOV(rot1);
                }
            }

            if (command == "setting.setGamma") {
                float rot1;
                if (arguments.size() == 1) {
                    std::istringstream(arguments[0]) >> rot1;
                    Abyss::minecraft->gameSettings->setGamma(rot1);
                }
            }
        }
    }
}

std::vector<std::string> CustomScript::extractArguments(const std::string& argsString) {
    std::vector<std::string> args;
    const size_t openBracketIndex = argsString.find('(');
    const size_t closeBracketIndex = argsString.find(')');

    if (openBracketIndex != std::string::npos && closeBracketIndex != std::string::npos && closeBracketIndex > openBracketIndex) {
        const std::string argsSubstring = argsString.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);
        std::istringstream iss(argsSubstring);
        std::string arg;

        while (std::getline(iss, arg, ',')) {
            args.push_back(arg);
        }
    }

    return args;
}

void CustomScript::onRenderTick() {
    ImGui::Begin("Custom Script Gui");
        const ImVec2 winPos = ImGui::GetWindowPos();
        const ImVec2 maxWinPos = ImVec2(winPos.x + ImGui::GetWindowWidth(), winPos.y + ImGui::GetWindowHeight());
        const ImVec2 size = ImVec2(ImGui::GetWindowSize().x - 1.0f, ImGui::GetWindowSize().y - 22.0f);

        ImGui::Begin("Custom Script Gui Background", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
        ClickGui::renderShadow(winPos, maxWinPos);
        ImGui::End();

        constexpr int bufferSize = 1024;
        if (text.size() < bufferSize)
            text.resize(bufferSize);

        ImGui::InputTextMultiline("AAAA", text.data(), text.size(), size, ImGuiInputTextFlags_AllowTabInput);

        lines.clear();

        std::istringstream iss(text.data());
        std::string line;
        while (std::getline(iss, line))
            lines.push_back(line);

    ImGui::End();
}