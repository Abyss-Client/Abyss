// class by sleepyfish for abyss recode
// February 2024 Firday 03:20 AM

#include "TextureUtils.h"

// Include OpenGL header (without an OpenGL loader) requires a bit of fiddling
#if defined(_WIN32) && !defined(APIENTRY)
#define APIENTRY __stdcall
#endif
#if defined(_WIN32) && !defined(WINGDIAPI)
#define WINGDIAPI __declspec(dllimport)
#endif

#include <gl/GL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../../../../../../libraries/stb/stb_image.h"
#include "../../../../../../assets/icons/abyssIcon.h"
#include "../../../../../../libraries/imgui/imgui.h"

void TextureUtils::unLoadTextures() {
    glDeleteTextures(1, &TextureUtils::abyssLogoSmall);
    TextureUtils::abyssLogoSmall = 0;
}

void TextureUtils::renderAbyssLogo(const float width, const float height) {
    if (!TextureUtils::alrLoaded) {
        TextureUtils::abyssLogoSmall = TextureUtils::loadTextureFromPNGArray(abyssIcon, 18241);
        TextureUtils::alrLoaded = true;
    }

    glDisable(GL_DEPTH_TEST);
    ImGui::Image((void*) (intptr_t) TextureUtils::abyssLogoSmall, ImVec2(width, height));
    glEnable(GL_DEPTH_TEST);
}

/**
 * @authors ChatGPT, SleepyFish
 * @param pngData a C array like 'unsigned char pngIcon[12468]'
 * @return texture ID as integer used to render an image
 */
unsigned int TextureUtils::loadTextureFromPNGArray(const unsigned char* pngData, int dataSize) {
    int width, height, channels;

    unsigned char* image = stbi_load_from_memory(pngData, dataSize, &width, &height, &channels, 0);
    if (image == nullptr)
        return 0;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

/**
 * @authors ChatGPT, SleepyFish
 * @param filename like 'C:/Users/Username/Downloads/GoofyPicture.png'
 * @return texture ID as integer used to render an image
 */
unsigned int TextureUtils::loadTextureFromFile(const char* filename) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image == nullptr)
        return 0;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

void TextureUtils::startScale(const float value) {
    glPushMatrix();
    glScalef(value, value, value);
}

void TextureUtils::stopScale() {
    glPopMatrix();
}