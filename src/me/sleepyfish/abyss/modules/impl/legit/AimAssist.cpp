// class by sleepyfish for abyss recode
// March 2024 Monday 11:37 PM

#include "AimAssist.h"

#include "../../../utils/Utils.h"
#include "../../settings/impl/SpaceSetting.h"

bool hasTimePassed = false;

AimAssist::AimAssist() : Module("Aim Assist", Category::Legit, "Helps you aim at players") {
    this->addSetting(AimAssist::aimMode);
    this->addSetting(AimAssist::range);
    this->addSetting(AimAssist::fovRange);
    this->addSetting(AimAssist::weaponOnly);
    this->addSetting(AimAssist::multiPoint);
    this->addSetting(new SpaceSetting());
    this->addSetting(AimAssist::increaseStrafe);
    this->addSetting(AimAssist::aimOffset);
    this->addSetting(AimAssist::prediction);
    this->addSetting(AimAssist::predictVal);
    this->addSetting(new SpaceSetting());
    this->addSetting(AimAssist::speedYaw);
    this->addSetting(AimAssist::speedPitch);
    this->addSetting(AimAssist::assistDelay);
    this->addSetting(new SpaceSetting());
    this->addSetting(AimAssist::ignoreFriends);
    this->addSetting(AimAssist::ignoreInvis);
    this->addSetting(AimAssist::ignoreBots);

    AimAssist::range->shouldFormat = true;
    AimAssist::fovRange->shouldFormat = true;
    AimAssist::aimOffset->shouldFormat = true;
    AimAssist::predictVal->shouldFormat = true;
    AimAssist::speedYaw->shouldFormat = true;
    AimAssist::speedPitch->shouldFormat = true;
    AimAssist::assistDelay->shouldFormat = true;
}

void AimAssist::onTick() {
    if (AimAssist::weaponOnly->isEnabled()) {
        if (!Utils::holdingWeapon())
            return;
    }

    EntityPlayerSP* playerVal = Abyss::minecraft->thePlayer;

    if (playerVal->isBlocking())
        return;

    EntityPlayer target = AimAssist::getTarget();

    if (!target.isNull()) {
        if (AimAssist::multiPoint->isEnabled()) {
            if (EnvUtils::Env->IsSameObject(Abyss::minecraft->getPointedEntity().getInstanceObject(), target.getInstanceObject()))
                return;
        }

        if (playerVal->getRotation().y >= 85.0f)
            return;

        Vector2 newRotations;

        const String modeVal = AimAssist::aimMode->getMode();

        if (modeVal.equals("Smok") || modeVal.equals("Blatant")) {
            newRotations = AimAssist::getRotations(target);
            playerVal->setRotation(newRotations);
            return;
        }

        if (modeVal.equals("Smooth") || modeVal.equals("Dont hit Me")) {
            Vector2 currentLookAngles = playerVal->getRotation();

            if (AimAssist::aimOffset->getValue() != 0.0f)
                currentLookAngles.y += (AimAssist::aimOffset->getValue() / 10.0f);

                float offset = 0.0f;

                if (AimAssist::prediction->isEnabled()) {
                    const float predictVal = (float) AimAssist::predictVal->getValue() / 2.0f;

                    if (Utils::holdingKey('D') && !Utils::holdingKey('A'))
                        offset -= predictVal;

                    if (Utils::holdingKey('A') && !Utils::holdingKey('D'))
                        offset += predictVal;
                }

                const float eHeight = target.getHeight() - 0.1f;
                const Vector3 ePos = target.getPosition();
                const Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);

                const Vector2 anglesHead = MathUtils::getAngles(playerVal->getEyePosition(), eHeadPos);
                const Vector2 differenceHead = MathUtils::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());

                const Vector2 anglesFoot = MathUtils::getAngles(playerVal->getEyePosition(), ePos);
                const Vector2 differenceFoot = MathUtils::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

                const float speedYawVal = (float) AimAssist::speedYaw->getValue();
                const float speedPitchVal = (float) AimAssist::speedPitch->getValue();

                float targetYaw = currentLookAngles.x + ((differenceHead.x + offset) / speedYawVal);

                if (modeVal.equals("Dont hit Me"))
                    targetYaw = currentLookAngles.x + ((differenceHead.x + offset) * speedYawVal);

                if ((currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y)) {
                    float targetPitchFoot = currentLookAngles.y + (differenceFoot.y / speedPitchVal);
                    float targetPitchHead = currentLookAngles.y + (differenceHead.y / speedPitchVal);

                    if (modeVal.equals("Dont hit Me")) {
                        targetPitchFoot = currentLookAngles.y + (differenceFoot.y * speedPitchVal);
                        targetPitchHead = currentLookAngles.y + (differenceHead.y * speedPitchVal);
                    }

                    const float diffFoot = currentLookAngles.y - targetPitchFoot;
                    const float diffHead = currentLookAngles.y - targetPitchHead;

                    MathUtils::min_float(diffFoot, -diffFoot);
                    MathUtils::min_float(diffHead, -diffHead);

                    float targetPitch;
                    if (diffFoot > diffHead) {
                        targetPitch = targetPitchFoot;
                    } else {
                        targetPitch = targetPitchHead;
                    }

                    newRotations = Vector2(targetYaw, targetPitch);
                } else {
                    newRotations = Vector2(targetYaw, currentLookAngles.y);
                }
        }

        if (!hasTimePassed) {
            const int delay = AimAssist::assistDelay->getValue();
            if (delay != 0)
                Sleep(delay);

            hasTimePassed = true;
        }

        if (hasTimePassed)
            playerVal->setRotation(newRotations);
    } else
        hasTimePassed = false;
}

// triangle for Syz $$$
EntityPlayer AimAssist::getTarget() {
    ArrayList<EntityPlayer> playerEntities = Abyss::minecraft->theWorld->getPlayerList();
    if (playerEntities.isEmpty())
        return nullptr;

    for (EntityPlayer target : playerEntities.getVector()) {
        if (EnvUtils::Env->IsSameObject(target.getInstanceObject(), Abyss::minecraft->thePlayer->getInstanceObject()))
            continue;

        if (!MathUtils::inFov(target, AimAssist::fovRange->getValue()))
            continue;

        if (!Utils::inRange(target, AimAssist::range->getValue()))
            continue;

        if (AimAssist::ignoreBots->isEnabled() && Utils::ignoreTarget(target, AimAssist::ignoreFriends->isEnabled()))
            continue;

        if (AimAssist::ignoreInvis->isEnabled() && target.isInvisible())
            continue;

        if (target.isDead())
            continue;

        if (!Abyss::minecraft->thePlayer->canEntityBeSeen(target))
            continue;

        return target;
    }

    return nullptr;
}

Vector2 AimAssist::getRotations(const EntityPlayer entity) {
    Vector2 rotations = MathUtils::getTargetRotations(entity);
    // printf( std::string("y:" + std::to_string(rotations.x) + ", p:" + std::to_string(rotations.y) + "\n").c_str() );

    if (AimAssist::aimMode->getMode().equals("Smok")) {
        float speedY = ( (float) AimAssist::speedYaw->getValue() / 100.0f );
        float speedP = ( (float) AimAssist::speedPitch->getValue() / 100.0f );

        if (speedY < 0.09f)
            speedY = 0.1f;

        if (speedP < 0.09f)
            speedP = 0.1f;

        EntityPlayerSP* playerVal = Abyss::minecraft->thePlayer;

        if (AimAssist::prediction->isEnabled()) {
            const float playerStrafe = playerVal->getMoveStrafe();

            if (playerStrafe != 0.0f) {
                const float predictVal = (float) AimAssist::predictVal->getValue() / 2.0f;

                if (playerVal->isSneaking()) {
                    if (playerStrafe > 0.2F)
                        rotations.x += predictVal / 4.0f;

                    if (playerStrafe < -0.2F)
                        rotations.x -= predictVal / 4.0f;
                } else {
                    if (playerStrafe > 0.6F)
                        rotations.x += predictVal;

                    if (playerStrafe < -0.6F)
                        rotations.x -= predictVal;
                }
            }
        }

        if (AimAssist::aimOffset->getValue() != 0.0f)
            rotations.y += (AimAssist::aimOffset->getValue() / 10.0f);

        rotations.y = MathUtils::smoothFloat(playerVal->getRotation().y, rotations.y, speedP);
        rotations.x = MathUtils::smoothFloat(playerVal->getRotation().x, rotations.x, speedY);

        const float sens = 0.5f;

        rotations.x = round(rotations.x / sens) * sens;
        rotations.y = round(rotations.y / sens) * sens;
    }

    return rotations;
}