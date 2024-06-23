// class by sleepyfish for abyss recode
// February 2024 Tuesday 12:50 AM

#ifndef NEWABYSS_VECTOR3_H
#define NEWABYSS_VECTOR3_H

#include <cmath>

class Vector3 {

public:

    float x { NAN };
    float y { NAN };
    float z { NAN };

    Vector3() {};

    Vector3 (const float x, const float y, const float z) :
        x(x), y(y), z(z)
    {}

    Vector3 operator + (const Vector3& rhs) const {
        return Vector3 (x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector3 operator + (const float rhs) const {
        return Vector3 (x + rhs, y + rhs, z + rhs);
    }

    Vector3 operator - (const Vector3& rhs) const {
        return Vector3 (x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector3 operator - (const float rhs) const {
        return Vector3 (x - rhs, y - rhs, z - rhs);
    }

    Vector3 operator * (const Vector3& rhs) const {
        return Vector3 (x * rhs.x, y * rhs.y, z * rhs.z);
    }

    Vector3 operator * (const float& rhs) const {
        return Vector3 (x * rhs, y * rhs, z * rhs);
    }

    Vector3 operator / (const float& rhs) const {
        return Vector3 (x / rhs, y / rhs, z / rhs);
    }

    Vector3& operator += (const Vector3& rhs) {
        return *this = *this + rhs;
    }

    Vector3& operator -= (const Vector3& rhs) {
        return *this = *this - rhs;
    }

    Vector3& operator *= (const float& rhs) {
        return *this = *this * rhs;
    }

    Vector3& operator /= (const float& rhs) {
        return *this = *this / rhs;
    }

    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]]
    float length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    [[nodiscard]]
    Vector3 normalize() const {
        return *this * (1 / length());
    }

    [[nodiscard]]
    Vector3 invert() const {
        return Vector3 { -x, -y, -z };
    }

    [[nodiscard]]
    float distance(const Vector3& rhs) const {
        return (*this - rhs).length();
    }

    [[nodiscard]]
    float dist() const {
        return sqrt(x * x + y * y);
    }

    [[nodiscard]]
    bool equals(float xx, float yy, float zz) const {
        return (x == xx && y == yy && z == zz);
    }

    [[nodiscard]]
    bool equals(const Vector3 vec) const {
        return (x == vec.y && y == vec.y && z == vec.z);
    }

};

#endif //NEWABYSS_VECTOR3_H