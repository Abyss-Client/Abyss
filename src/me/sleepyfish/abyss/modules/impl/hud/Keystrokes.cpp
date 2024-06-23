// class by sleepyfish for abyss recode
// March 2024 Thursday 11:50 PM

#include "Keystrokes.h"
#include "../../../utils/Utils.h"

Keystrokes::Keystrokes() : HudModule("Keystrokes", "Render ur keystrokes on the HUD") {
    this->custom         = true;
    this->autoSetPos     = false;

    this->wAnimation     = new SimpleAnimation(1.0f);
    this->sAnimation     = new SimpleAnimation(1.0f);
    this->aAnimation     = new SimpleAnimation(1.0f);
    this->dAnimation     = new SimpleAnimation(1.0f);
    this->spaceAnimation = new SimpleAnimation(1.0f);

    this->clearSettings();
    this->addSetting(Keystrokes::boxSize);
    this->addSetting(Keystrokes::boxGap);

    Keystrokes::boxSize->shouldFormat = true;
    Keystrokes::boxGap->shouldFormat = true;
}

void Keystrokes::renderMod() {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    const float windowX = ImGui::GetWindowPos().x;
    const float windowY = ImGui::GetWindowPos().y;

    this->wAnimation->updateTimer();
    this->sAnimation->updateTimer();
    this->aAnimation->updateTimer();
    this->dAnimation->updateTimer();
    this->spaceAnimation->updateTimer();

    const float fontSize = 20.0f;

    const int addStaticPos = this->boxSize->getValue() + boxGap->getValue();
    const int addPublicPos = addStaticPos + this->boxSize->getValue() + boxGap->getValue();

    this->width = (addPublicPos + this->boxSize->getValue() + 4);
    this->height = (addPublicPos + this->boxSize->getValue());

    const ImVec4 colorW = this->getColor('W', this->wAnimation);
    const ImVec2 topLeftW(windowX + addStaticPos, windowY);
    const ImVec2 bottomRightW(topLeftW.x + this->boxSize->getValue(), topLeftW.y + this->boxSize->getValue());
    drawList->AddRectFilled(topLeftW, bottomRightW, ImColor(colorW));
    const ImVec2 centerW((topLeftW.x + bottomRightW.x) / 2.0f, (topLeftW.y + bottomRightW.y) / 2.0f - 2.0f);
    const ImVec2 textSizeW = ImGui::CalcTextSize("W");
    drawList->AddText(ClickGui::fontBold, fontSize, ImVec2(centerW.x - textSizeW.x / 2.0f, centerW.y - textSizeW.y / 2.0f), this->getFont(), "W");

    const ImVec4 colorS = this->getColor('S', this->sAnimation);
    const ImVec2 topLeftS(windowX + addStaticPos, windowY + addStaticPos);
    const ImVec2 bottomRightS(topLeftS.x + this->boxSize->getValue(), topLeftS.y + this->boxSize->getValue());
    drawList->AddRectFilled(topLeftS, bottomRightS, ImColor(colorS));
    const ImVec2 centerS((topLeftS.x + bottomRightS.x) / 2.0f, (topLeftS.y + bottomRightS.y) / 2.0f - 2.0f);
    const ImVec2 textSizeS = ImGui::CalcTextSize("S");
    drawList->AddText(ClickGui::fontBold, fontSize, ImVec2(centerS.x - textSizeS.x / 2.0f, centerS.y - textSizeS.y / 2.0f), this->getFont(), "S");

    const ImVec4 colorA = this->getColor('A', this->aAnimation);
    const ImVec2 topLeftA(windowX, windowY + addStaticPos);
    const ImVec2 bottomRightA(topLeftA.x + this->boxSize->getValue(), topLeftA.y + this->boxSize->getValue());
    drawList->AddRectFilled(topLeftA, bottomRightA, ImColor(colorA));
    const ImVec2 centerA((topLeftA.x + bottomRightA.x) / 2.0f, (topLeftA.y + bottomRightA.y) / 2.0f - 2.0f);
    const ImVec2 textSizeA = ImGui::CalcTextSize("A");
    drawList->AddText(ClickGui::fontBold, fontSize, ImVec2(centerA.x - textSizeA.x / 2.0f, centerA.y - textSizeA.y / 2.0f), this->getFont(), "A");

    const ImVec4 colorD = this->getColor('D', this->dAnimation);
    const ImVec2 topLeftD(windowX + addPublicPos, windowY + addStaticPos);
    const ImVec2 bottomRightD(topLeftD.x + this->boxSize->getValue(), topLeftD.y + this->boxSize->getValue());
    drawList->AddRectFilled(topLeftD, bottomRightD, ImColor(colorD));
    const ImVec2 centerD((topLeftD.x + bottomRightD.x) / 2.0f, (topLeftD.y + bottomRightD.y) / 2.0f - 2.0f);
    const ImVec2 textSizeD = ImGui::CalcTextSize("D");
    drawList->AddText(ClickGui::fontBold, fontSize, ImVec2(centerD.x - textSizeD.x / 2.0f, centerD.y - textSizeD.y / 2.0f), this->getFont(), "D");

    const ImVec4 colorSpace = this->getColor(' ', this->spaceAnimation);
    const ImVec2 topLeftSpace(windowX, windowY + addPublicPos);
    const ImVec2 bottomRightSpace(topLeftSpace.x + addPublicPos + this->boxSize->getValue(), topLeftSpace.y + this->boxSize->getValue() - 4);
    drawList->AddRectFilled(topLeftSpace, bottomRightSpace, ImColor(colorSpace));
}

ImVec4 Keystrokes::getColor(int key, SimpleAnimation* ani) {
    ani->setAnimation(Utils::holdingKey(key) ? 190.0f : 90.0f, 6.0f);

    const ImVec4 col = this->getBackground();

    return {
        col.x, col.y, col.z, (ani->getValue() / 255.0f)
    };
}