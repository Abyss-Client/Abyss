// class by sleepyfish for abyss recode
// February 2024 Tuesday 2:17 AM

#include "../ClickGui.h"
#include "../../utils/Utils.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    if (ClickGui::guiTitle.toChar() != "") {
        if (msg == WM_KEYDOWN) {
            if (wParam < 256) {

                if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (wParam == 'H')) {
                    ClickGui::onMenuOpen();
                } else if (wParam == ClickGui::guiKeybind) {
                    ClickGui::onMenuOpen();
                } else {
                    if (wParam == VK_ESCAPE && ClickGui::isGuiOpen) {
                        ClickGui::isGuiOpen = false;
                        return false;
                    }

                    /* Keybind stuff that isnt used yet
                    if (ClientUtils::keybind_isBinding) {
                        ClientUtils::keybind_lastKey = (int) wParam;
                        ClientUtils::keybind_isBinding = false;
                    }
                    */

                    if (!ClickGui::isGuiOpen) {
                        if (Utils::canLegitWork()) {
                            for (Module* mod : Abyss::modManager.getModules().getVector()) {
                                if (mod->getKeybind() == (int) wParam)
                                    mod->toggle();
                            }
                        }
                    }
                }
            }
        }

        if (ClickGui::isGuiOpen) {
            ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
            return true;
        }
    }

    return CallWindowProc(original_wndProc, hwnd, msg, wParam, lParam);
}

void ClickGui::hook_onKey() {
    original_wndProc = (template_WndProc) SetWindowLongPtr(ClickGui::handleWindow, GWLP_WNDPROC, (LONG_PTR) hook_WndProc);
    Abyss::logger.log("| Gui - Info: Done On key");
}

void ClickGui::unhook_onKey() {
    SetWindowLongPtr(ClickGui::handleWindow, GWLP_WNDPROC, (LONG_PTR) original_wndProc);
}