// class by sleepyfish for abyss recode
// February 2024 Tuesday 2:08 AM

#include <thread>
#include "../ClickGui.h"
#include "../../client/Abyss.h"
#include "../../../../../../libraries/imgui/imgui_impl_opengl2.h"
#include "../../../../../../libraries/imgui/imgui_impl_win32.h"
#include "../../../../../../libraries/minhook/minhook.h"

std::once_flag setupFlag;

typedef bool(__stdcall* template_wglSwapBuffers) (HDC hdc);
template_wglSwapBuffers original_wglSwapBuffers;

bool __stdcall hook_wglSwapBuffers(_In_ HDC hdc) {
    ClickGui::handleDeviceContext = hdc;
    ClickGui::handleWindow = WindowFromDC(hdc);
    ClickGui::originalGLContext = wglGetCurrentContext();

    std::call_once(setupFlag, [&] {
        ClickGui::hook_onKey();
        ClickGui::setupImgui();

        Abyss::notify.inject();
    });

    wglMakeCurrent(ClickGui::handleDeviceContext, ClickGui::menuGLContext);

    if (ClickGui::draw) {

        // Update Client color
        if (ClientUtils::color_chroma) {
            const ImVec4 rainbow = ColorUtils::getRainbow(
                    ClientUtils::color_frequency / 100.0f, ClientUtils::color_brightness / 100.0f,
                    ClientUtils::color_gamma / 100.0f, ClientUtils::color_alpha / 100.0f
            );

            ClientUtils::clientColor[0] = rainbow.x;
            ClientUtils::clientColor[1] = rainbow.y;
            ClientUtils::clientColor[2] = rainbow.z;
            ClientUtils::clientColor[3] = rainbow.w;

            const ImColor mainColor = ImColor(ClientUtils::clientColor[0], ClientUtils::clientColor[1], ClientUtils::clientColor[2], ClientUtils::clientColor[3]);

            ImVec4 *colors = ImGui::GetStyle().Colors;

            colors[ImGuiCol_Border] = mainColor;
            colors[ImGuiCol_Separator] = mainColor;
            colors[ImGuiCol_CheckMark] = mainColor;
            colors[ImGuiCol_SliderGrab] = mainColor;
            colors[ImGuiCol_SliderGrabActive] = mainColor;
            colors[ImGuiCol_ScrollbarGrabActive] = mainColor;
        }

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ClientUtils::getWindowPosMin());
        ImGui::SetNextWindowSize(ClientUtils::getWindowPosMax());

        ImGui::Begin("Overlay", 0, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
        {
            ImGui::PushFont(ClickGui::fontDefault);

            for (Module *mod: Abyss::modManager.getModules().getVector())
                if (mod->isEnabled())
                    mod->onRenderTick();

            Abyss::notify.render();

            ImGui::PopFont();

            if (ClickGui::isGuiOpen) {
                ImGui::PushFont(ClickGui::fontDefault);
                ClickGui::renderGui();
                ImGui::PopFont();
            } else {
                if (!ClickGui::fixedAlpha) {
                    if (ImGui::GetStyle().Alpha < 0.1f)
                        ImGui::GetStyle().Alpha = 1.0f;

                    ClickGui::fixedAlpha = true;
                }
            }
        }
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    wglMakeCurrent(ClickGui::handleDeviceContext, ClickGui::originalGLContext);
    return original_wglSwapBuffers(hdc);
}

void ClickGui::hook_RenderSwapBuffers() {
    const LPVOID wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
    Abyss::logger.log("| Gui - Info: Done SwapBuffers");
    MH_CreateHook(wglSwapBuffers, (LPVOID)hook_wglSwapBuffers, (LPVOID*)&original_wglSwapBuffers);
    MH_EnableHook(wglSwapBuffers);
}

void ClickGui::unhook_RenderSwapBuffers() {
    ImGui_ImplOpenGL2_DestroyFontsTexture();
    ImGui_ImplOpenGL2_DestroyDeviceObjects();
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
}