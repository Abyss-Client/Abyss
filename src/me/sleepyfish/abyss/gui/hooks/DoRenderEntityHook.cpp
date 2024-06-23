// class by sleepyfish for abyss recode
// February 2024 Tuesday 5:57 AM

#include "../ClickGui.h"
#include "../../java/mapper/Mapper.h"
#include "../../../../../../libraries/minhook/minhook.h"
#include "../../client/Abyss.h"
#include <gl/GLU.h>

typedef void(__thiscall* doRenderEntityFunc)(jobject entity, jdouble x, jdouble y, jdouble z, jfloat yaw, jfloat pitch, jboolean p_188391_10);

doRenderEntityFunc originalDoRenderEntity;

void callBeforeRender() {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(0.0f, -1100000.0f);
}

void callAfterRender() {
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(0.0f, 1100000.0f);
}

// ----

void __fastcall hookedDoRenderEntity(jobject entity, jdouble x, jdouble y, jdouble z, jfloat yaw, jfloat pitch, jboolean p_188391_10) {
    callBeforeRender();
    Abyss::logger.log("onRender");
    originalDoRenderEntity(entity, x, y, z, yaw, pitch, p_188391_10);
    callAfterRender();
}

void ClickGui::hook_doRenderEntity() {
    jmethodID methodID = Mapper::mapper_voids["renderManager_doRenderEntity"];
    void* doRenderEntityAddr = reinterpret_cast<void*>(methodID);

    MH_CreateHook(doRenderEntityAddr, &hookedDoRenderEntity, (LPVOID*) &originalDoRenderEntity);
    MH_EnableHook(doRenderEntityAddr);
}

void ClickGui::unhook_doRenderEntity() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
}