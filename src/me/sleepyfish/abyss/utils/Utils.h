// class by sleepyfish for abyss recode
// February 2024 Sunday 6:21 PM

#ifndef NEWABYSS_UTILS_H
#define NEWABYSS_UTILS_H

#include <utility>

#include "../client/Abyss.h"
#include "MathUtils.h"

class Utils {
protected:
    static inline bool alrChecked = false;

public:

    static inline bool lagOut = false;
    static inline bool lagIn = false;

    static void startOutPacketLag() {
        lagOut = true;
    }

    static void stopOutPacketLag() {
        lagOut = false;
    }

    static void startInPacketLag() {
        lagIn = true;
    }

    static void stopInPacketLag() {
        lagIn = false;
    }

    static bool canLegitWork(bool ignoreGuiState = false) {
        if (Utils::hasIngameFocus()) {
            if (!Abyss::minecraft->isNull()) {
                if (!Abyss::minecraft->theWorld->isNull() && Abyss::minecraft->thePlayer->isNull()) {
                    if (!ignoreGuiState) {
                        if (Abyss::minecraft->inGui())
                            return false;
                    }

                    if (!Abyss::minecraft->thePlayer->isNull()) {
                        if (!Abyss::minecraft->thePlayer->isDead())
                            return true;
                    }
                }
            }
        }

        return false;
    }

    static bool inRange(Entity a, double b) {
        return MathUtils::getDistanceToEntity(std::move(a)) <= b;
    }

    static ItemStack getCurrentItem() {
        return Abyss::minecraft->thePlayer->getInventory().getCurrentItem();
    }

    static jboolean isCurrentGuiInstanceOf(const String& a) {
        if (Abyss::minecraft->getCurrentScreen() == nullptr)
            return false;

        return Utils::instanceOf(Abyss::minecraft->getCurrentScreen(), Mapper::mapper_classes[a.toChar()]);
    }

    static jboolean sameTeamAs(Entity a) {
        if (!ClientUtils::module_friends)
            return false;

        return Abyss::minecraft->thePlayer->getTeam().getInstanceObject() == a.getTeam().getInstanceObject();
    }

    static jboolean isMoving() {
        return Abyss::minecraft->thePlayer->getMoveForward() != 0.0f || Abyss::minecraft->thePlayer->getMoveStrafe() != 0.0f;
    }

    static jboolean isMovingForward() {
        return Abyss::minecraft->thePlayer->getMoveForward() > 0.0f;
    }

    static jboolean isMovingBackwards() {
        return Abyss::minecraft->thePlayer->getMoveForward() < 0.0f;
    }

    static jboolean holdingWeapon() {
        return holdingSword() || holdingAxe() || holdingShears();
    }

    static jboolean instanceOf(jobject a, jclass b) {
        if (a == nullptr) return false;
        return EnvUtils::Env->IsInstanceOf(a, b);
    }

    static jboolean holdingSword() {
        return Utils::holding(Mapper::mapper_classes["ItemSword"]);
    }

    static jboolean holdingPickaxe() {
        return Utils::holding(Mapper::mapper_classes["ItemPickaxe"]);
    }

    static jboolean holdingAxe() {
        return Utils::holding(Mapper::mapper_classes["ItemAxe"]);
    }

    static jboolean holdingShears() {
        return Utils::holding(Mapper::mapper_classes["ItemShears"]);
    }

    static jboolean holdingBlock() {
        return Utils::holding(Mapper::mapper_classes["ItemBlock"]);
    }

    static jboolean holdingFood() {
        return Utils::holding(Mapper::mapper_classes["ItemFood"]);
    }

    static bool holding(const String& a) {
        return Utils::getCurrentItem().getName().toLowercase().contains(a.toLowercase().toString());
    }

    static bool holding(jclass a) {
        return Utils::instanceOf(Utils::getCurrentItem().getItem().getInstanceObject(), a);
    }

    static String getCurrentItemName() {
        return Utils::getCurrentItem().getName().toLowercase().toString();
    }

    static jboolean inInventory() {
        if (!Abyss::minecraft->inGui())
            return false;

        return !Utils::isCurrentGuiInstanceOf("GuiInventory");
    }

    static jboolean overAir(const jdouble a) {
        const Vector3 pos = Abyss::minecraft->thePlayer->getPosition();

        return Abyss::minecraft->theWorld->isAirBlock (
                pos.x, pos.y - a, pos.z
        );
    }

    static bool switchTo(String a) {
        a = a.toLowercase();

        if (Utils::holding(a))
            return true;

        for (int i = 0; i < 9; ++i) {
            ItemStack iS = Abyss::minecraft->thePlayer->getInventory().getIndexItem(i);

            if (!iS.isNull()) {
                if (iS.getName().toLowercase().contains(a.toString())) {
                    Abyss::minecraft->thePlayer->getInventory().setCurrentItem(i);
                    return true;
                }
            }
        }

        return false;
    }

    static bool holdingMiddle() {
        return (GetAsyncKeyState(VK_MBUTTON) & 0x8000);
    }

    static bool holdingRight() {
        return (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
    }

    static bool holdingLeft() {
        return (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
    }

    static bool holdingKey(int key) {
        return (GetAsyncKeyState(key) & 0x8000);
    }

    static std::string getNameFromObject(jobject a) {
        if (a == nullptr)
            return "null";

        jclass objectClass = EnvUtils::Env->GetObjectClass(a);
        if (objectClass == nullptr)
            return "null";

        jmethodID toStringMethod = EnvUtils::Env->GetMethodID(objectClass, "toString", "()Ljava/lang/String;");
        if (toStringMethod == nullptr)
            return "null";

        auto stringObject = (jstring) EnvUtils::Env->CallObjectMethod(a, toStringMethod);
        if (stringObject == nullptr)
            return "null";

        const char* str = EnvUtils::Env->GetStringUTFChars(stringObject, nullptr);
        if (str == nullptr)
            return "null";

        const std::string nig = str;

        EnvUtils::Env->ReleaseStringUTFChars(stringObject, str);

        return nig;
    }

    static void callGarbageCollector() {
        Abyss::java.callGarbageCollector();
    }

    static bool hasIngameFocus() {
        return (GetForegroundWindow() == FindWindowA("LWJGL", nullptr));
    }

    static bool contains(const std::string& a, const std::string& b) {
        return a.find(b) != std::string::npos;
    }

    static void hideCorsor() {
        SetCursor(nullptr);
    }

    static void checkForName(const String& a) {
        if (a.equals("sleepyfish_yt"))
            return;

        if (a.equals("nickthetrick321"))
            return;

        if (a.equals("xenpvp"))
            return;

        if (a.equals("richelie"))
            return;

        if (a.equals("laurelxd"))
            return;

        if (a.equals("sirlennox"))
            return;

        ClientUtils::crash();
    }

    static bool ignoreTarget(Entity target, bool ignoreFriends = true) {
        if (ClientUtils::module_antiBot) {
            if (target.isNull())
                return true;

            // Add Friends check like if (Friends::friendArray.contains(target)) return true;
            if (ignoreFriends) {
                if (Utils::sameTeamAs(target))
                    return true;
            }

            if (target.isDead())
                return true;

            if (target.isInvisible())
                return true;

            if (target.getUUID().getVersion() == 2)
                return true;

            return target.getTicksExisted() > 99999
                || target.getName().startsWith("[NPC]")
                || target.getName().contains("-")
                || target.getName().contains("[")
                || target.getName().contains("]")
                || target.getName().contains(" ")
                || target.getName().getLength() <= 2;
        }

        return false;
    }

};

#endif //NEWABYSS_UTILS_H