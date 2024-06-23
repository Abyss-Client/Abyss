// class by sleepyfish for abyss recode
// February 2024 Saturday 10:59 AM

#ifndef NEWABYSS_CLICKUTILS_H
#define NEWABYSS_CLICKUTILS_H

#include <chrono>
#include <random>
#include "../gui/ClickGui.h"
#include "MathUtils.h"

class ClickUtils {

private:
    POINT pos_cursor;

    int keyCode;
    int keyButton;
    int keyStateDown;
    int keyStateFinalUp;
    LPARAM param;

    float nextCps = 1;
    long long lastClickTime = 0;

public:

    ClickUtils(int keyCode) :
        keyCode(keyCode),
        keyButton(0),
        keyStateDown(0),
        keyStateFinalUp(0)
    { this->init(); }

    void init() {
        GetCursorPos(&this->pos_cursor);
        param = MAKELPARAM(this->pos_cursor.x, this->pos_cursor.y);

        if (keyCode == 0) {
            keyButton = MK_LBUTTON;
            keyStateDown = WM_LBUTTONDOWN;
            keyStateFinalUp = WM_LBUTTONUP;
            return;
        }

        if (keyCode == 1) {
            keyButton = MK_RBUTTON;
            keyStateDown = WM_RBUTTONDOWN;
            keyStateFinalUp = WM_RBUTTONUP;
            return;
        }
    }

    void update(int min, int max, bool extraRandom = false) {
        long long milliLeft = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        int finalMin = min;
        int finalMax = max;
        if (extraRandom) {
            finalMin = MathUtils::randomInt(min - 6, min + 8);
            finalMax = MathUtils::randomInt(max - 6, max + 8);
        }

        if (this->lastClickTime == 0)
            this->lastClickTime = milliLeft;

        if ((milliLeft - this->lastClickTime) < (1000 / nextCps))
            return;

        SendMessage(ClickGui::handleWindow, keyStateDown, keyButton, param);
        SendMessage(ClickGui::handleWindow, keyStateFinalUp, keyButton, param);

        this->lastClickTime = milliLeft;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(finalMin, finalMax);
        nextCps = distrib(gen);
    }
};

#endif //NEWABYSS_CLICKUTILS_H