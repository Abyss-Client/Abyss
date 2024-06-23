// class by sleepyfish for abyss recode
// February 2024 Tuesday 12:22 AM

#ifndef NEWABYSS_GRADIENTCOLORUTIL_H
#define NEWABYSS_GRADIENTCOLORUTIL_H

#include "../../../../../libraries/imgui/imgui.h"

class ColorUtils {
public:

    static ImVec4 getGradient(const ImVec4& color1, const ImVec4& color2, float seconds, float offset = 0) {
        const float time = (float) ImGui::GetTime() + (offset / 2.0f);
        const float half_duration = seconds / 2.0f;
        float t = fmod(time, seconds) / half_duration;

        if (t < 0.0f)
            t += 1.0f;

        if (t > 1.0f)
            t = 2.0f - t;

        const float red   = color1.x * (1.0f - t) + color2.x * t;
        const float green = color1.y * (1.0f - t) + color2.y * t;
        const float blue  = color1.z * (1.0f - t) + color2.z * t;

        return { red, green, blue, 1.0f };
    }

    static ImVec4 getRainbow(float frequency, float brightness, float gamma, float alpha, float offset = 0) {
        const float time = (float) ImGui::GetTime() + (offset * 2.0f);
        const float r = sinf(frequency * time + 0.0f) * gamma + brightness;
        const float g = sinf(frequency * time + 2.0f) * gamma + brightness;
        const float b = sinf(frequency * time + 4.0f) * gamma + brightness;
        return { r, g, b, alpha };
    }
};

#endif //NEWABYSS_GRADIENTCOLORUTIL_H