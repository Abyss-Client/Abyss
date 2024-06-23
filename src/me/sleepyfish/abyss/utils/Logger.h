// class by sleepyfish for abyss recode

#ifndef NEWABYSS_LOGGER_H
#define NEWABYSS_LOGGER_H

#include <cstdio>
#include <Windows.h>
#include "ClientUtils.h"
#include "type/Class.h"

class Logger : public Class {

public:
    static inline FILE* file;
    static inline int fastLogCount = 1;
    static inline HWND consoleWindow;

    void inject() override {
        if (Logger::isNull) {
            AllocConsole();
            SetConsoleTitle(ClientUtils::getNameWithVersion().toChar());
            this->consoleWindow = GetConsoleWindow();

            SetConsoleSize(600, 800);
            freopen_s(&this->file, "CONOUT$", "w", stdout);

            Logger::nextLine();
            Logger::log("       db         88");
            Logger::log("      d88b        88");
            Logger::log("     d8'`8b       88");
            Logger::log("    d8'  `8b      88,dPPYba,   8b       d8  ,adPPYba,  ,adPPYba,");
            Logger::log("   d8YaaaaY8b     88P'    \"8a  `8b     d8'  I8[    \"\"  I8[    \"\"");
            Logger::log("  d8\"\"\"\"\"\"\"\"8b    88       d8   `8b   d8'    `\"Y8ba,    `\"Y8ba,");
            Logger::log(" d8'        `8b   88b,   ,a8\"    `8b,d8'          ]8I        ]8I");
            Logger::log("d8'          `8b  8Y\"Ybbd8\"'       Y88'     `\"YbbdP\"'  `\"YbbdP\"'");
            Logger::log("                                   d8'");
            Logger::log("                                 d8'");
            Logger::nextLine();
            Logger::log("============================== Inject Start ==============================");
            Logger::nextLine();

            Logger::isNull = false;
        }
    }

    void unInject() override {
        if (!Logger::isNull) {
            ShowWindow(GetConsoleWindow(), false);
            clearerr_s(this->file);
            FreeConsole();
            Logger::isNull = true;
        }
    }

    void hide() {
        if (!Logger::isNull)
            ShowWindow(GetConsoleWindow(), false);
    }

    void SetConsoleSize(int width, int height) {
        RECT rect;
        GetWindowRect(this->consoleWindow, &rect);
        MoveWindow(this->consoleWindow, rect.left, rect.top, width, height, TRUE);
    }

    void nextLine() {
        printf("\n");
    }

    void log() {
        log("Fast log:", this->fastLogCount++);
    }

    void log(String text) {
        printf(" %s \n", text.toChar());
    }

    void log(String text, String text2) {
        printf(" %s %s \n", text.toChar(), text2.toChar());
    }

    void log(String text, int format) {
        printf(" %s %d \n", text.toChar(), format);
    }

    void logF(String text, float format) {
        printf(" %s %f \n", text.toChar(), format);
    }

    void log(String text, int format, int format2) {
        printf(" %s %d %d \n", text.toChar(), format, format2);
    }

    void log(String text, int format, String text2) {
        printf(" %s %d %s \n", text.toChar(), format, text2.toChar());
    }

};

#endif //NEWABYSS_LOGGER_H