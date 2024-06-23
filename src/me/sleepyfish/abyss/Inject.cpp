// class by sleepyfish for abyss recode

#include "windows.h"
#include "thread"
#include "client/Abyss.h"

void Init(HMODULE mod) {
    Abyss::inject(mod);

    std::thread([&] {
        PlaySoundA(R"(C:\Windows\Media\Speech On.wav)", mod, 0);
    }).detach();

    while (Abyss::isInjected) {
        Abyss::onTickUpdate();
        Sleep(2);
    }

    std::thread([&] {
        PlaySoundA(R"(C:\Windows\Media\Speech Off.wav)", mod, 0);
    }).detach();

    Abyss::unInject();
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (ClientUtils::isProcessRunning(L"javaw.exe") || ClientUtils::isProcessRunning(L"java.exe")) {
        if (dwReason == true) {
            if (!DisableThreadLibraryCalls(hModule))
                return false;

            const HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Init, hModule, 0, 0);
            if (hThread != nullptr)
                CloseHandle(hThread);
        }

        return true;
    } else {
        return true;
    }
}