// class by sleepyfish for abyss recode
// February 2024 Tuesday 12:49 AM

#ifndef NEWABYSS_VECTOR2_H
#define NEWABYSS_VECTOR2_H

#include <cmath>

struct Vector2 {
    float x { NAN };
    float y { NAN };

    Vector2 operator - (const Vector2& rhs) const {
        return Vector2(x - rhs.x, y - rhs.y);
    }

    Vector2 operator + (const Vector2& rhs) const {
        return Vector2(x + rhs.x, y + rhs.y);
    }

    bool operator == (const Vector2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    Vector2 Invert() const {
        return Vector2{ -x, -y };
    }

    void clear() {
        x = 0.0f;
        y = 0.0f;
    }
};

#endif //NEWABYSS_VECTOR2_H