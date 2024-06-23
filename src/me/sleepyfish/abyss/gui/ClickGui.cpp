// class by sleepyfish for abyss recode
// February 2024 Tuesday 12:56 AM

#include "ClickGui.h"
#include "../utils/ClientUtils.h"
#include "../client/Abyss.h"
#include "../../../../../libraries/imgui/imgui_impl_opengl2.h"
#include "../../../../../libraries/imgui/imgui_impl_win32.h"
#include "../../../../../libraries/imgui/imgui_internal.h"
#include "../utils/ClickGuiUtils.h"
#include "../utils/Utils.h"
#include "../modules/settings/impl/SliderSetting.h"
#include "../modules/settings/impl/ModeSetting.h"
#include "../modules/settings/impl/ColorSetting.h"
#include "../modules/settings/impl/InfoSetting.h"

void ClickGui::inject() {
    if (ClickGui::isNull) {
        Abyss::logger.log("/ Gui - Info: Inject");

        String name = "";
        if (Abyss::mapper.useForgeMappings()) {
            name = "Forge";
        } else
        if (Abyss::mapper.useVanillaMappings()) {
            name = "Vanilla";
        } else
        if (Abyss::mapper.useLunarMappings()) {
            name = "Lunar";
        }

        ClickGui::guiTitle = ClientUtils::getNameWithVersion() + " : " + name;
        ClickGui::isGuiOpen = false;
        ClickGui::guiKeybind = VK_DELETE;

        Abyss::logger.log("| Gui - Info: Init Variables");

        ClickGui::hook_RenderSwapBuffers();
        ClickGui::hook_Packets();
        ClickGui::hook_onRender();
        ClickGui::hook_doRenderEntity();

        Abyss::logger.log("\\ Gui - Info: Inject Done");
        Abyss::logger.nextLine();

        ClickGui::isNull = false;
    }
}

void ClickGui::unInject() {
    if (!ClickGui::isNull) {
        Abyss::logger.log("| Gui - Info: UnInject");

        ClickGui::unhook_doRenderEntity();
        ClickGui::unhook_onKey();
        ClickGui::unhook_onRender();
        ClickGui::unhook_Packets();
        ClickGui::unhook_RenderSwapBuffers();

        ClickGui::guiKeybind = 0;
        ClickGui::isGuiOpen = false;
        ClickGui::guiTitle = "";

        TextureUtils::unLoadTextures();

        // Restore old context
        wglMakeCurrent(ClickGui::handleDeviceContext, ClickGui::originalGLContext);
        wglDeleteContext(ClickGui::menuGLContext);
        ImGui::DestroyContext();

        Abyss::logger.log("| Gui - Info: UnInject Done");
        Abyss::logger.nextLine();

        ClickGui::isNull = true;
    }
}

void ClickGui::renderGui() {
    // Intro fade animation
    if (isFadingIn) {
        guiAlpha += ImGui::GetIO().DeltaTime * 8;
        if (guiAlpha >= 1.0f) {
            guiAlpha = 1.0f;
            isFadingIn = false;
        }
    }

    ImGui::GetStyle().Alpha = guiAlpha;

    ImGui::SetNextWindowPos(ClientUtils::getWindowPosMin());
    ImGui::SetNextWindowSize(ClientUtils::getWindowPosMax());

    ImGui::Begin("Main Gui", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoFocusOnAppearing);

    if (Abyss::isDebugging) {
        bool tr = true;
        ImGui::ShowDemoWindow(&tr);
    }

    // ShaderUtils::renderBackground();

    if (ClientUtils::gui_background) {
        ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ClientUtils::getWindowPosMin(),
            ImVec2(ClientUtils::getWindowPosMax().x + 5, ClientUtils::getWindowPosMax().y + 5),
            ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.8f), ImGui::GetImColor32(ImGuiCol_Border),
            ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.8f), ImGui::GetImColor32(ImGuiCol_Border)
        );

        String fps = std::to_string((int) ImGui::GetIO().Framerate);
        String clientInfo = ClientUtils::getNameWithVersion() + " | Fps: " + fps;
        const char *ab = clientInfo.toChar();

        ImGui::SetOffset(15, 15);
        TextureUtils::renderAbyssLogo(64.0f, 64.0f);

        const float startX = 80.0f;
        const float endX = 170.0f;

        const float startY = 25.0f;
        const float endY = 25.0f;

        ClickGui::renderShadow(ImVec2(startX, startY), ImVec2(startX + endX, startY + endY));
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(startX, startY), ImVec2(startX + endX, startY + endY), ImGui::GetImColor32(ImGuiCol_Border), ClientUtils::gui_rounding);
        ImGui::GetWindowDrawList()->AddText(ClickGui::fontDefault, 20.0f, ImVec2(startX + 9.0f, startY + 2.0f), IM_COL32_WHITE, ab);

        if (ClientUtils::cat_background) {
            ClickGui::renderShadow(ClickGui::legitCatPos, ClickGui::legitCatPosMax);
            ClickGui::renderShadow(ClickGui::visualCatPos, ClickGui::visualCatPosMax);
            ClickGui::renderShadow(ClickGui::blatantCatPos, ClickGui::blatantCatPosMax);
            ClickGui::renderShadow(ClickGui::otherCatPos, ClickGui::otherCatPosMax);
            ClickGui::renderShadow(ClickGui::uselessCatPos, ClickGui::uselessCatPosMax);
            ClickGui::renderShadow(ClickGui::hudCatPos, ClickGui::hudCatPosMax);
            ClickGui::renderShadow(ClickGui::clientCatPos, ClickGui::clientCatPosMax);
        }

        ImGui::End();
    }

    for (const Category cat: Abyss::modManager.getCategories().getVector()) {
        const ArrayList<Module*> modulesInCat = Abyss::modManager.getModulesByCategory(cat);
        if (modulesInCat.isEmpty())
            break;

        const String name = Abyss::modManager.getCategoryName(cat);
        const String idName = name + "-ID";

        ImGui::Begin(idName.toChar(), nullptr, ClickGui::categoryFlags);

        const ImColor mainColor = ImColor(ClientUtils::clientColor[0], ClientUtils::clientColor[1], ClientUtils::clientColor[2], ClientUtils::clientColor[3]);

        if (ClientUtils::cat_title_background) {
            const ImVec2 winPos = ImGui::GetWindowPos();
            const ImVec2 maxWinPos = ImVec2(winPos.x + ImGui::GetWindowWidth(), winPos.y + ImGui::GetWindowHeight());

            if (name.equals("Legit")) {
                ClickGui::legitCatPos = winPos;
                ClickGui::legitCatPosMax = maxWinPos;
            }

            if (name.equals("Visual")) {
                ClickGui::visualCatPos = winPos;
                ClickGui::visualCatPosMax = maxWinPos;
            }

            if (name.equals("Blatant")) {
                ClickGui::blatantCatPos = winPos;
                ClickGui::blatantCatPosMax = maxWinPos;
            }

            if (name.equals("Other")) {
                ClickGui::otherCatPos = winPos;
                ClickGui::otherCatPosMax = maxWinPos;
            }

            if (name.equals("Useless")) {
                ClickGui::uselessCatPos = winPos;
                ClickGui::uselessCatPosMax = maxWinPos;
            }

            if (name.equals("Hud")) {
                ClickGui::hudCatPos = winPos;
                ClickGui::hudCatPosMax = maxWinPos;
            }

            if (ClientUtils::cat_roundAllSides) {
                ImGui::GetCurrentWindow()->DrawList->AddRectFilled(ImVec2(winPos.x + 0.5f, winPos.y - 0.5f),
                ImVec2(maxWinPos.x + 0.5f, winPos.y + 30), mainColor, ClientUtils::gui_rounding);
            } else {
                ImGui::GetCurrentWindow()->DrawList->AddRectFilled(ImVec2(winPos.x + 0.5f, winPos.y - 0.5f),
                ImVec2(maxWinPos.x + 0.5f, winPos.y + 30), mainColor, ClientUtils::gui_rounding, ImDrawFlags_RoundCornersTop);
            }
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(ClickGui::categoryPadding, ClickGui::categoryPadding));
        ImGui::Spacing();

        if (ClientUtils::cat_centerTitles) {
            const float titleWidth = ClickGui::fontMedium->CalcTextSizeA(ClickGui::fontMedium->FontSize, FLT_MAX, 0.0f, name.toChar()).x;
            ImGui::SetOffsetX(((ImGui::GetWindowWidth() / 2.0f) - (titleWidth / 2.0f)));
        } else {
            ImGui::SetOffsetX(ClickGui::categoryPadding);
        }

        ImGui::SetOffsetY(ImGui::GetOffsetY() - 6);
        ImGui::PushFont(ClickGui::fontMedium);
        ImGui::Text("%s", name.toChar());
        ImGui::PopFont();

        ImGui::SetOffsetX(ClickGui::categoryPadding);
        ImGui::SetOffsetY(ClickGui::categoryPadding * 3);

        // for modules in category
        for (Module* mod: modulesInCat.getVector()) {
            if (mod->isEnabled())
                mod->onGuiRenderTick();

            float settingHeight = 0.0f;

            // for module box settingHeight
            for (const Setting* setting: mod->getSettings().getVector()) {
                if (setting->getType() != 5 && setting->getType() != 4)
                    settingHeight += 24.0f;
            }

            ImGui::ModuleSectionSleepy(mod, ImVec2(210.0f, 56.3f + settingHeight));

            if (mod->settingsExpanded) {
                ImGui::Spacing();

                int randomBypass = 0;

                ImGui::PopFont();
                ImGui::PushFont(ClickGui::fontSmaller);

                // for module settings
                for (Setting *setting: mod->getSettings().getVector()) {
                    switch (setting->getType()) {
                        case 0: {
                            ImGui::Spacing();
                            break;
                        }

                        case 1: {
                            auto *boolSetting = (BoolSetting*) setting;

                            ImGui::CheckSliderAbyss(setting->getName().toChar(), setting->getDesc().toChar(), &boolSetting->enabled);

                            break;
                        }

                        case 2: {
                            auto *slideSetting = (SliderSetting*) setting;

                            if (slideSetting->shouldFormat) {
                                const std::string spaces(randomBypass, ' ');
                                randomBypass++;

                                ImGui::SliderIntAbyss(spaces.c_str(), setting->getDesc().toChar(), &slideSetting->currVal, slideSetting->getMinValue(), slideSetting->getMaxValue(), (slideSetting->getName() + ": %d").toChar());
                            } else {
                                ImGui::SliderIntAbyss(setting->getName().toChar(), setting->getDesc().toChar(), &slideSetting->currVal, slideSetting->getMinValue(), slideSetting->getMaxValue());
                            }

                            break;
                        }

                        case 3: {
                            auto *modeSetting = (ModeSetting*) setting;

                            if (ImGui::BeginMenu(setting->getName().toChar())) {
                                const String currentMode = modeSetting->getMode();

                                for (const String& mode: modeSetting->getModes()) {
                                    if (ImGui::MenuItem(mode.toChar(), nullptr, currentMode.equals(mode), true))
                                        modeSetting->setMode(mode);
                                }

                                ImGui::EndMenu();
                            }

                            break;
                        }

                        case 4: {
                            auto *colorSetting = (ColorSetting*) setting;

                            const ImVec4 color = colorSetting->getColor();
                            float r[4] = {color.x, color.y, color.z, 1.0f};

                            const ImVec4 a = ImGui::ColorPickerSmellon(colorSetting->getName().toChar(), r, colorSetting->shouldRenderName());
                            ImGui::SameLine(45, 0);
                            colorSetting->setColor(a);

                            break;
                        }

                        case 5: {
                            auto *textSetting = (TextSetting*) setting;

                            const std::string spaces(randomBypass, ' ');
                            randomBypass++;

                            char* textData = &textSetting->text.getData();
                            std::string stdText = textSetting->text.toString();

                            constexpr int bufferSize = 2024;
                            if (stdText.size() < bufferSize)
                                stdText.resize(bufferSize);

                            ImGui::InputTextMultiline(spaces.c_str(), textData, stdText.size(), ImVec2(140, 24), ImGuiInputTextFlags_CtrlEnterForNewLine);
                            break;
                        }

                        case 6: {
                            auto *infoSetting = (InfoSetting*) setting;

                            ImGui::SeparatorText(infoSetting->getName().toChar());

                            break;
                        }
                    }
                }

                ImGui::PopFont();
                ImGui::PushFont(ClickGui::fontDefault);
            }

            ImGui::EndChild();
            ImGui::SetOffsetX(ClickGui::categoryPadding);
        }

        ImGui::PopStyleVar();
        ImGui::End();
    }

    {
        ImGui::Begin("Client Category", nullptr, ClickGui::categoryFlags);
        ImVec2 winPos = ImGui::GetWindowPos();
        ImVec2 maxWinPos = ImVec2(winPos.x + ImGui::GetWindowWidth(), winPos.y + ImGui::GetWindowHeight());
        ImColor mainColor = ImColor(ClientUtils::clientColor[0], ClientUtils::clientColor[1],
                                    ClientUtils::clientColor[2], ClientUtils::clientColor[3]);

        ClickGui::clientCatPos = winPos;
        ClickGui::clientCatPosMax = maxWinPos;

        float width = 200.0f;
        float height = 160.0f;
        float smallWidth = width / 1.5f;
        float smallHeight = height / 1.5f - 22.0f;

        if (ClickGui::fixedAlpha) {
            ImGuiStyle &style = ImGui::GetStyle();

            style.ScrollbarRounding = ClientUtils::gui_rounding;
            style.WindowRounding = ClientUtils::gui_rounding;
            style.ChildRounding = ClientUtils::gui_rounding;
            style.FrameRounding = ClientUtils::gui_rounding;
            style.PopupRounding = ClientUtils::gui_rounding;
            style.GrabRounding = ClientUtils::gui_rounding;
            style.TabRounding = ClientUtils::gui_rounding;

            ClickGui::fixedAlpha = false;
        }

        if (ClientUtils::cat_title_background) {
            if (ClientUtils::cat_roundAllSides) {
                ImGui::GetCurrentWindow()->DrawList->AddRectFilled(ImVec2(winPos.x + 0.5f, winPos.y - 0.5f), ImVec2(maxWinPos.x + 0.5f, winPos.y + 30), mainColor, ClientUtils::gui_rounding);
            } else {
                ImGui::GetCurrentWindow()->DrawList->AddRectFilled(ImVec2(winPos.x + 0.5f, winPos.y - 0.5f), ImVec2(maxWinPos.x + 0.5f, winPos.y + 30), mainColor, ClientUtils::gui_rounding, ImDrawFlags_RoundCornersTop);
            }
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(ClickGui::categoryPadding, ClickGui::categoryPadding));
        ImGui::Spacing();

        if (ClientUtils::cat_centerTitles) { float titleWidth = ClickGui::fontMedium->CalcTextSizeA(ClickGui::fontMedium->FontSize, FLT_MAX, 0.0f, "Client").x;
            ImGui::SetOffsetX(((ImGui::GetWindowWidth() / 2.0f) - (titleWidth / 2.0f)));
        } else {
            ImGui::SetOffsetX(ClickGui::categoryPadding);
        }

        ImGui::SetOffsetY(ImGui::GetOffsetY() - 6);
        ImGui::PushFont(ClickGui::fontMedium);
        ImGui::Text("Client");
        ImGui::PopFont();

        ImGui::SetOffsetX(ClickGui::categoryPadding);
        ImGui::SetOffsetY(ImGui::GetOffsetX() + (ClickGui::categoryPadding * 2));

        {
            ImGui::BeginChildSleepy("info", ImVec2(width - 20, height + 30), true);

            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("Supportet Mappings:");
            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("- Lunar 1.8.9");
            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("- Forge 1.8.9");
            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("- Vanilla 1.8.9");

            ImGui::Spacing();
            ImGui::Text(ClientUtils::getNameWithVersion().toChar());
            ImGui::Text("Built: " __DATE__);

            ImGui::EndChildSleepy(5);
        }

        // ---

        {
            ImGui::BeginChildSleepy("authors", ImVec2(smallWidth + 20, height + 30), true);
            ImGui::Text("Authors");
            ImGui::Spacing();

            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("Owner:");
            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("- SleepyFish");

            ImGui::Spacing();

            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("Devs:");
            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("- Smellon");
            ImGui::Text("");
            ImGui::SameLine();
            ImGui::Text("- DevOfDeath");

            ImGui::EndChildSleepyH();
        }

        // ---

        {
            ImGui::BeginChildSleepy("ending_shit", ImVec2(width + 135, height - 45), true,
                                    ImGuiWindowFlags_NoScrollbar);

            if (ImGui::Button("Detach"))
                Abyss::isInjected = false;

            ImGui::SameLine(0, 10);

            if (ImGui::Button("Crash")) {
                PlaySoundA("C:\\Windows\\Media\\Windows Hardware Remove.wav", Abyss::HModule, 0);
                ClientUtils::crash();
            }

            ImGui::SameLine(0, 10);

            if (ImGui::Button("Discord"))
                ClientUtils::openUrl(ClientUtils::abyss_discord);

            ImGui::SameLine(0, 10);

            ImGui::ColorPickerSmellon(" Client Color", ClientUtils::clientColor, true,
                                      ImGuiColorEditFlags_PickerHueBar |
                                      ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview |
                                      ImGuiColorEditFlags_NoDragDrop |
                                      ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions);
            {
                ImVec4 *colors = ImGui::GetStyle().Colors;

                colors[ImGuiCol_Border] = mainColor;
                colors[ImGuiCol_Separator] = mainColor;
                colors[ImGuiCol_CheckMark] = mainColor;
                colors[ImGuiCol_SliderGrab] = mainColor;
                colors[ImGuiCol_SliderGrabActive] = mainColor;
                colors[ImGuiCol_ScrollbarGrabActive] = mainColor;
            }

            if (ImGui::Button("Gui Settings"))
                ImGui::OpenPopup("##popup_settings");

            ImGui::SameLine(0, 10);

            if (ImGui::Button("Module Settings"))
                ImGui::OpenPopup("##popup_module_settings");

            ImGui::CheckSliderAbyss("Antibot", &ClientUtils::module_antiBot);
            ImGui::SameLine(0, 10);
            ImGui::CheckSliderAbyss("Friends", &ClientUtils::module_friends);

            if (ImGui::BeginPopup("##popup_settings")) {
                ImGui::SeparatorText("Gui Settings");
                // ImGui::CheckSliderAbyss("New Gui", &ClientUtils::gui_newGui);
                ImGui::CheckSliderAbyss("Background", &ClientUtils::gui_background);

                if (ImGui::SliderIntAbyss("Rounding", &ClientUtils::gui_rounding, 0, 12)) {
                    ImGuiStyle &style = ImGui::GetStyle();

                    style.ScrollbarRounding = ClientUtils::gui_rounding;
                    style.WindowRounding = ClientUtils::gui_rounding;
                    style.ChildRounding = ClientUtils::gui_rounding;
                    style.FrameRounding = ClientUtils::gui_rounding;
                    style.PopupRounding = ClientUtils::gui_rounding;
                    style.GrabRounding = ClientUtils::gui_rounding;
                    style.TabRounding = ClientUtils::gui_rounding;
                }

                ImGui::SliderFloatAbyss("Global Alpha", &ImGui::GetStyle().Alpha, 0.20f, 1.0f);

                ImGui::Spacing();
                ImGui::SeparatorText("Category Settings");
                ImGui::SliderIntAbyss("Category Padding", &ClickGui::categoryPadding, 0, 35);
                ImGui::CheckSliderAbyss("Category Shadow", &ClientUtils::cat_background);
                ImGui::CheckSliderAbyss("Center Category titles", &ClientUtils::cat_centerTitles);
                ImGui::CheckSliderAbyss("Render Category title background", &ClientUtils::cat_title_background);
                ImGui::CheckSliderAbyss("Round Category title background", &ClientUtils::cat_roundAllSides);

                /*
                ImGui::Spacing();
                ImGui::SeparatorText("Languages");
                ImGui::Spacing();

                if (ImGui::Button("German"))
                    Translator::currentLanguage = Translator::German;

                ImGui::SameLine(0, 10);

                if (ImGui::Button("English"))
                    Translator::currentLanguage = Translator::English;

                ImGui::SameLine(0, 10);

                if (ImGui::Button("Espanol"))
                    Translator::currentLanguage = Translator::Espanol;

                ImGui::SameLine(0, 10);

                if (ImGui::Button("Russian"))
                    Translator::currentLanguage = Translator::Russian;

                // ImGui::SameLine(0, 10);

                if (ImGui::Button("Hungarian"))
                    Translator::currentLanguage = Translator::Hungarian;

                ImGui::SameLine(0, 10);

                if (ImGui::Button("Romanian"))
                    Translator::currentLanguage = Translator::Romanian;
                */

                ImGui::EndPopup();
            }

            if (ImGui::BeginPopup("##popup_module_settings")) {
                int randomBypass = 0;

                for (const Category cat : Abyss::modManager.getCategories().getVector()) {
                    ImGui::SeparatorText(ModuleManager::getCategoryName(cat).toChar());

                    for (Module* modInCat : Abyss::modManager.getModulesByCategory(cat).getVector()) {

                        const std::string spaces(randomBypass, ' ');
                        randomBypass++;

                        char* textData = &modInCat->modName.getData();
                        std::string stdText = modInCat->modName.toString();

                        constexpr int bufferSize = 2024;
                        if (stdText.size() < bufferSize)
                            stdText.resize(bufferSize);

                        ImGui::InputTextMultiline(spaces.c_str(), textData, stdText.size(), ImVec2(140, 24), ImGuiInputTextFlags_CtrlEnterForNewLine);

                        ImGui::SameLine(160, 5);
                        ImGui::CheckSliderAbyss( String("Hide" + spaces).toChar() , &modInCat->hideModule);
                        ImGui::SameLine(250, 5);

                        ImGui::BeginChildFrame(randomBypass, ImVec2(30, 28));
                            if (ImGui::Button("    ")) {
                                modInCat->modName = modInCat->getOldName();
                            }
                        ImGui::EndChildFrame();
                    }
                }

                ImGui::EndPopup();
            }

            ImGui::Text(" ");
            ImGui::Text("Thread sleep delay");
            //ImGui::SliderIntAbyss("  ", &ClientUtils::event_threadSleep, 10, 80);

            if (ImGui::Button("Call Garbage Collector"))
                Utils::callGarbageCollector();

            ImGui::EndChild();
        }

        ImGui::PopStyleVar();
    }

    ImGui::End();
}

/**
 * @code Horrible way of doing this
 */
void ClickGui::renderShadow(ImVec2 posMin, ImVec2 posMax) {
    posMin.x -= 2.0f;
    posMin.y -= 2.0f;
    posMax.x += 2.0f;
    posMax.y += 2.0f;

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posMin.x - 5.0f, posMin.y - 5.0f), ImVec2(posMax.x + 5.0f, posMax.y + 5.0f),
    ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.2f), ClientUtils::gui_rounding + 1.4f);

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posMin.x - 4.0f, posMin.y - 4.0f), ImVec2(posMax.x + 4.0f, posMax.y + 4.0f),
    ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.4f), ClientUtils::gui_rounding + 1.2f);

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posMin.x - 3.0f, posMin.y - 3.0f), ImVec2(posMax.x + 3.0f, posMax.y + 3.0f),
    ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.4f), ClientUtils::gui_rounding + 1.0f);

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posMin.x - 2.0f, posMin.y - 2.0f), ImVec2(posMax.x + 2.0f, posMax.y + 2.0f),
    ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.6f), ClientUtils::gui_rounding + 0.8f);

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posMin.x - 1.0f, posMin.y - 1.0f), ImVec2(posMax.x + 1.0f, posMax.y + 1.0f),
    ImGui::GetImColor32(ImGuiCol_BorderShadow, 0.8f), ClientUtils::gui_rounding + 0.6f);
}

void ClickGui::onMenuOpen() {
// Toggle GUI open/close state

    ClickGui::isGuiOpen = !ClickGui::isGuiOpen;

    if (ClickGui::isGuiOpen) {
        guiAlpha = 0.0f;
        isFadingIn = true;
        isFadingOut = false;
    } else {
        isFadingIn = false;
        isFadingOut = true;
    }

    // Mouse hide
    //     ImGui::GetIO().MouseDrawCursor = ClickGui::isGuiOpen;

    if (ClickGui::isGuiOpen) {
        Abyss::notify.updateWindowPos();

        // Check for false mappings and renew them
        jobject thePlayer = EnvUtils::Env->GetObjectField(Abyss::minecraft->getInstanceObject(), Mapper::mapper_fields["minecraft_thePlayer"]);
        // jobject theWorld = EnvUtils::Env->GetObjectField(Abyss::minecraft->getInstanceObject(), Mapper::mapper_fields["minecraft_theWorld"]);
        jobject serverData = EnvUtils::Env->GetObjectField(Abyss::minecraft->getInstanceObject(), Mapper::mapper_fields["minecraft_currentServerData"]);

        if (thePlayer != nullptr) {
            Abyss::minecraft->thePlayer = new EntityPlayerSP(Abyss::minecraft->getInstanceObject());
            EnvUtils::Env->DeleteLocalRef(thePlayer);
            Abyss::logger.log("Updated thePlayer");
        }

        // if (theWorld != nullptr) {
        //     Abyss::minecraft->theWorld = new WorldClient(Abyss::minecraft->getInstanceObject());
        //     EnvUtils::Env->DeleteLocalRef(theWorld);
        //     Abyss::logger.log("Updated theWorld");
        // }

        if (serverData != nullptr) {
            Abyss::minecraft->serverData = new ServerData(Abyss::minecraft->getInstanceObject());
            EnvUtils::Env->DeleteLocalRef(serverData);
            Abyss::logger.log("Updated serverData");
        }

        // if (thePlayer != nullptr && theWorld != nullptr)
        //     Abyss::logger.nextLine();
    }
}

void ClickGui::setupImgui() {
    ClickGui::menuGLContext = wglCreateContext(ClickGui::handleDeviceContext);
    wglMakeCurrent(ClickGui::handleDeviceContext, ClickGui::menuGLContext);

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLint m_viewport[4];
    glGetIntegerv(GL_VIEWPORT, m_viewport);
    glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 0);
    */

    ClickGui::imGuiContext = ImGui::CreateContext();

    ClickGuiUtils::applyDefaultTheme();
    ClickGuiUtils::applyPurpleTheme();
    ClickGuiUtils::applyFonts();

    ImGui_ImplWin32_Init(ClickGui::handleWindow);
    ImGui_ImplOpenGL2_Init();
}