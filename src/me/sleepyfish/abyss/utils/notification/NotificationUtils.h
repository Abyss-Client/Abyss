#ifndef NEWABYSS_NOTIFICATIONUTIL_H
#define NEWABYSS_NOTIFICATIONUTIL_H

#include <unordered_map>
#include "Notification.h"
#include "../type/String.h"
#include "../type/ArrayList.h"
#include "../../../../../../libraries/imgui/imgui.h"
#include "../opengl/TextureUtils.h"
#include "../../gui/ClickGui.h"

class NotificationUtils : Class {

private:
    ArrayList<Notification*> notifications;
    float notificationDuration = 5.0f;
    float notificationSpacing = 1.0f;
    ImVec2 notificationStartPosition;
    int notificationCounter = 0;

    struct NotificationState {
        bool visible;
        float alpha;
    };

    std::unordered_map<std::string, NotificationState> notificationStates;

public:

    void inject() override {
        if (this->isNull) {
            this->isNull = false;
        }
    }

    void unInject() override {
        if (!this->isNull) {
            this->notifications.clear();
            this->notificationDuration = 0;
            this->notificationSpacing = 0;
            this->notificationStartPosition = ImVec2(0, 0);
            this->notificationCounter = 0;
            this->notificationStates.clear();
            this->isNull = true;
        }
    }

    void updateWindowPos() {
        notificationStartPosition = ImVec2(ImGui::GetIO().DisplaySize.x - 10, ImGui::GetIO().DisplaySize.y - 10);
    }

    void notify(const String& message, const String& format) {
        this->notify(message + format);
    }

    void notify(const String& message) {
        if (!this->isNull) {
            const String uniqueTitle = "###notification_" + std::to_string(notificationCounter++);
            notifications.add(new Notification(uniqueTitle, message, ImGui::GetTime() + notificationDuration));
            notificationStates[uniqueTitle.toChar()] = { true, 0.0f };
        }
    }

    void render() {
        if (!this->isNull) {
            this->update();

            ImVec2 position = notificationStartPosition;
            for (Notification* notification: notifications.getVector()) {
                auto &state = notificationStates[notification->title.toChar()];

                ImGui::SetNextWindowPos(position, ImGuiCond_Always, ImVec2(1, 1));
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, state.alpha);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(ClickGui::categoryPadding, ClickGui::categoryPadding));

                ImGui::Begin(notification->title.toChar(), nullptr,
                             ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);


                const ImVec2 winPos = ImGui::GetWindowPos();
                const ImVec2 maxWinPos = ImVec2(winPos.x + ImGui::GetWindowWidth(), winPos.y + ImGui::GetWindowHeight());

                notification->shadowPosMin = winPos;
                notification->shadowPosMax = maxWinPos;

                if (state.visible && state.alpha < 1.0f) {
                    state.alpha += ImGui::GetIO().DeltaTime;
                    if (state.alpha > 1.0f)
                        state.alpha = 1.0f;
                } else {
                    if (!state.visible && state.alpha > 0.0f) {
                        state.alpha -= ImGui::GetIO().DeltaTime;
                        if (state.alpha < 0.0f)
                            state.alpha = 0.0f;
                    }
                }

                ImGui::Text("%s", notification->message.toChar());
                ImGui::PopStyleVar();
                ImGui::End();

                position.y -= ImGui::GetFontSize() - notificationSpacing;

                if (ClientUtils::cat_background)
                    ClickGui::renderShadow(notification->shadowPosMin, notification->shadowPosMax);
            }
        }
    }

    void update() {
        if (!this->isNull) {
            auto currentTime = ImGui::GetTime();
            auto notificationVector = getNotifications();

            for (Notification* it : notificationVector.getVector()) {
                auto &state = notificationStates[it->title.toString()];

                if (currentTime > it->expireTime) {
                    float fadeOutDuration = 1.0f;
                    float elapsedTime = currentTime - it->expireTime;

                    if (elapsedTime < fadeOutDuration) {
                        state.alpha = 1.0f - (elapsedTime / fadeOutDuration);
                    } else {
                        notificationVector.remove(it);
                        continue;
                    }
                }
            }

            notifications.clear();
            for (auto notification : notificationVector.getVector())
                notifications.add(notification);
        }
    }

    ArrayList<Notification*> getNotifications() {
        return notifications;
    }

};

#endif //NEWABYSS_NOTIFICATIONUTIL_H
