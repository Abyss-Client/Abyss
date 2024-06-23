// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#ifndef NEWABYSS_CLIENTUTILS_H
#define NEWABYSS_CLIENTUTILS_H

#include "windows.h"
#include "winbase.h"
#include <tlhelp32.h>
#include "ColorUtils.h"
#include "type/String.h"
#include "../../../../../libraries/imgui/imgui.h"

class ClientUtils {

public:

    // Client main color
    static inline float clientColor[4] { 0.55f, 0.39f, 0.78f, 1.0f };

    // Gui Settings
    static inline bool gui_background = true;
    static inline int  gui_rounding = 4;

    // Color Settings
    static inline int color_frequency = 40;
    static inline int color_brightness = 20;
    static inline int color_gamma = 60;
    static inline int color_alpha = 80;

    static inline bool color_chroma = false;

    // Static Target / Module settings
    static inline bool module_antiBot = true;
    static inline bool module_friends = true;

    // Category Settings
    static inline bool cat_background = true;
    static inline bool cat_title_background = true;
    static inline bool cat_roundAllSides = false;
    static inline bool cat_centerTitles = true;

    // Links
    static inline const String abyss_discord  = "discord.gg/7JXXvkufJK";
    static inline const String abyss_website  = "sites.google.com/view/sleepy-abyss";

    static inline const String smellonYoutube = "www.youtube.com/@Smellon";
    static inline const String sleepyYoutube  = "www.youtube.com/@SleepyFishh";

    static String getName() {
        return "Abyss";
    }

    static String getVersion() {
        return "2.0";
    }

    static String getNameWithVersion() {
        return getName() + " v" + getVersion();
    }

    static String getDiscord() {
        return "https://discord.gg/sBUmdAmZtr";
    }

    static void messageBox(const String message) {
        MessageBoxA(0, message.toChar(), getNameWithVersion().toChar(), 0);
    }

    static void openUrl(const String url) {
        const String lll = "start https://";
        std::system( (lll + url).toChar() );
    }

    static void crash() {
        std::exit(INFINITY);
    }

    static ImVec2 getWindowPosMax() {
        return ImVec2(ImGui::GetIO().DisplaySize.x + 12, ImGui::GetIO().DisplaySize.y + 12);
    }

    static const ImVec2 getWindowPosMin() {
        return ImVec2(-6, -6);
    }

    static bool isProcessRunning(const wchar_t* processName) {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnapshot, &pe32)) {
            do {
                wchar_t szExeFile[MAX_PATH];
                MultiByteToWideChar(CP_ACP, 0, pe32.szExeFile, -1, szExeFile, MAX_PATH);

                if (wcscmp(szExeFile, processName) == 0) {
                    CloseHandle(hSnapshot);
                    return true;
                }
            } while (Process32Next(hSnapshot, &pe32));
        } else {
            CloseHandle(hSnapshot);
        }

        CloseHandle(hSnapshot);
        return false;
    }

};

#endif //NEWABYSS_CLIENTUTILS_H