// class by sleepyfish for abyss recode
// February 2024 Tuesday 3:25 AM

#include <WinSock2.h>
#include "../ClickGui.h"
#include "../../../../../../libraries/minhook/minhook.h"
#include "../../client/Abyss.h"
#include "../../utils/Utils.h"

int(__stdcall* g_origWSASend)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
int __stdcall WSASendHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

    while (Utils::lagOut)
        Sleep(1);

    return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

int(__stdcall* g_origWSARecv)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
int __stdcall WSARecvHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

    while (Utils::lagIn)
        Sleep(1);

    return g_origWSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

void ClickGui::hook_Packets() {
    MH_CreateHookApi(L"Ws2_32.dll", "WSASend", WSASendHook, (void**)&g_origWSASend);
    Abyss::logger.log("| Gui - Info: Done Out Packet");
    MH_CreateHookApi(L"Ws2_32.dll", "WSARecv", WSARecvHook, (void**)&g_origWSARecv);
    Abyss::logger.log("| Gui - Info: Done In Packet");

    MH_EnableHook(MH_ALL_HOOKS);
}

void ClickGui::unhook_Packets() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
}