// class by sleepyfish for abyss recode
#ifndef NEWABYSS_MEMORYSTATS_H
#define NEWABYSS_MEMORYSTATS_H

#include <cstdint>
#include "sysinfoapi.h"

class MemoryStats {
public:
    static uint64_t totalMemory() {
        MEMORYSTATUSEX memStatus;
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);
        return static_cast<uint64_t>(memStatus.ullTotalPhys);
    }

    static uint64_t freeMemory() {
        MEMORYSTATUSEX memStatus;
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);
        return static_cast<uint64_t>(memStatus.ullAvailPhys);
    }

    static uint64_t maxMemory() {
        MEMORYSTATUSEX memStatus;
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);
        return static_cast<uint64_t>(memStatus.ullTotalVirtual);
    }

    static long bytesToMb(const long bytes) {
        return bytes / 1024L / 1024L;
    }
};

#endif //NEWABYSS_MEMORYSTATS_H