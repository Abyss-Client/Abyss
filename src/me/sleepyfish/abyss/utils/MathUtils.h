// class by sleepyfish for abyss recode
// February 2024 Tuesday 12:46 AM

#ifndef NEWABYSS_MATHUTILS_H
#define NEWABYSS_MATHUTILS_H

#include <cmath>
#include <random>
#include "type/Vector2.h"
#include "type/Vector3.h"
#include "../client/Abyss.h"

#define PI 3.14159f

class MathUtils {

public:

    static float wrapAngleTo180(float angle) {
        angle = std::fmod(angle, 360.0f);

        if (angle >= 180.0f)
            angle -= 360.0f;

        if (angle < -180.0f)
            angle += 360.0f;

        return angle;
    }

    static float randomFloat(float min, float max) {
        const float f = (float) rand() / RAND_MAX;
        return min + f * (max - min);
    }

    static int randomInt(int min, int max) {
        //const int f = rand() / RAND_MAX;
        //return min + f * (max - min + 1);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    static int min_int(int min1, int min2) {
        return (int) std::fminl(min1, min2);
    }

    static float min_float(float min1, float min2) {
        return std::fminf(min1, min2);
    }

    static double min_double(double min1, double min2) {
        return std::fmin(min1, min2);
    }

    static int max_int(int max1, int max2) {
        return (int) std::fmaxl(max1, max2);
    }

    static float max_float(float min1, float min2) {
        return std::fmaxf(min1, min2);
    }

    static double max_double(double min1, double min2) {
        return std::fmax(min1, min2);
    }

    static float toRadians(float val) {
        return val * (PI / 180.0f);
    }

    static double sin(double val) {
        return std::sin(val);
    }

    static double cos(double val) {
        return std::cos(val);
    }

    static double sqrt(double val) {
        return std::sqrt(val);
    }

    static double pow(float left, int right) {
        return std::pow(left, right);
    }

    static Vector2 vec_wrapAngleTo180(Vector2 angle) {
        return {
            wrapAngleTo180(angle.x), wrapAngleTo180(angle.y)
        };
    }

    static Vector2 getTargetRotations(EntityPlayer target) {
        if (target.isNull()) {
            return {0, 0};
        } else {
            EntityPlayer* thePlayer = Abyss::minecraft->thePlayer;
            const Vector2 thePlayerRot = thePlayer->getRotation();
            const Vector3 thePlayerPos = thePlayer->getPosition();

            const Vector3 targetPos = target.getPosition();
            const double targetHeight = target.getHeight() * 0.85f;
            const double playerHeight = thePlayer->getHeight() * 0.85f;

            const double diffX = targetPos.x - thePlayerPos.x;
            const double diffY = target.getPosition().y + targetHeight * 0.9f - (thePlayerPos.y + playerHeight);
            const double diffZ = targetPos.z - thePlayerPos.z;

            const float yaw = (float) (atan2(diffZ, diffX) * 180.0f / PI) - 90.0f;
            const auto pitch = (float) (-(atan2(diffY, MathUtils::sqrt(diffX * diffX + diffZ * diffZ)) * 180.0f / PI));

            return {
                thePlayerRot.x + MathUtils::wrapAngleTo180(yaw - thePlayerRot.x),
                thePlayerRot.y + MathUtils::wrapAngleTo180(pitch - thePlayerRot.y)
            };
        }
    }

    static float coterminal(float angle) {
        return std::fmod(angle, 180.0f) < 0.0f ? angle + 170.0f : angle;
    }

    static float magnitude(Vector3 v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    static Vector3 crossProduct(Vector3 v1, Vector3 v2) {
        return {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }

    static float shortestDistance(Vector3 p, Vector3 a, Vector3 b) {
        const Vector3 ab {
            b.x - a.x, b.y - a.y, b.z - a.z
        };

        const Vector3 cp = MathUtils::crossProduct (
            Vector3 {
                p.x - a.x, p.y - a.y, p.z - a.z
            }, ab
        );

        return MathUtils::magnitude(cp) / MathUtils::magnitude(ab);
    }

    static Vector2 getAngles(Vector3 pos, Vector3 pos1) {
        const double d_x = pos1.x - pos.x;
        const double d_y = pos1.y - pos.y;
        const double d_z = pos1.z - pos.z;

        const double hypo = MathUtils::sqrt(d_x * d_x + d_z * d_z);
        const float yaw = MathUtils::radiantsToDeg(atan2(d_z, d_x)) - 90.0f;
        const float pitch = MathUtils::radiantsToDeg(-atan2(d_y, hypo));

        return {
            yaw, pitch
        };
    }

    static float radiantsToDeg(float x) {
        return x * 180.0f / PI;
    }

    static float degToRadiants(float x) {
        return x * PI / 180.0f;
    }

    static float smoothFloat(float from, float to, float speed) {
        float angle = MathUtils::wrapAngleTo180(to - from);
        if (angle > speed)
            angle = speed;

        if (angle < -speed)
            angle = -speed;

        return from + angle;
    }

    static float fovToEntity(EntityPlayer target) {
        const double x = target.getPosition().x - Abyss::minecraft->thePlayer->getPosition().x;
        const double z = target.getPosition().z - Abyss::minecraft->thePlayer->getPosition().z;
        const double w = atan2(x, z) * 57.2957795f;
        return (float) (w * -1.0);
    }

    static bool inFov(EntityPlayer target, float fov) {
        fov *= 0.5f;
        double angleToTarget = fmod(Abyss::minecraft->thePlayer->getRotation().x - fovToEntity(target), 360.0f) + 540.0f;
        angleToTarget = fmod(angleToTarget, 360.0f) - 180.0f;
        return (angleToTarget > 0.0f && angleToTarget < fov) || (-fov < angleToTarget && angleToTarget < 0.0f);
    }

    static double getDistanceToEntity(Entity entity) {
        return MathUtils::getDistanceToVector(entity.getPosition());
    }

    static double getDistanceToVector(Vector3 vec) {
        Vector3 diff = Abyss::minecraft->thePlayer->getPosition() - vec;

        if (diff.x == 0 && diff.y == 0 && diff.z == 0)
            return 0;

        return MathUtils::sqrt (
            MathUtils::pow(diff.x, 2) + MathUtils::pow(diff.y, 2) + MathUtils::pow(diff.z, 2)
        );
    }

};

#endif //NEWABYSS_MATHUTILS_H