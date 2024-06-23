// class by sleepyfish for abyss recode
// February 2024 Tuesday 2:22 AM

#include "../ClickGui.h"
#include "../../../../../../libraries/minhook/minhook.h"
#include "../../client/Abyss.h"
#include <gl/GL.h>

typedef __int64(__fastcall* Java_org_lwjgl_opengl_GL11_nglTexEnvi) (void** env, void** clazz, GLenum target, GLenum pname, GLint param, void** functionpointer);
Java_org_lwjgl_opengl_GL11_nglTexEnvi original_glTexEnvi;

__int64 hknglTexEnvi(void** env, void** clazz, GLenum target, GLenum pname, GLint param, void** functionpointer) {
    // EventChams event(target, pname, param);
    // Abyss::eventManager.call(event);
    return original_glTexEnvi(env, clazz, target, pname, param, functionpointer);
}

void ClickGui::hook_onRender() {
    MH_CreateHookApi(L"lwjgl64", "Java_org_lwjgl_opengl_GL11_nglTexEnvi", hknglTexEnvi, (LPVOID*)&original_glTexEnvi);
    Abyss::logger.log("| Gui - Info: Done On Render");
    MH_EnableHook(MH_ALL_HOOKS);
}

void ClickGui::unhook_onRender() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
}