#ifndef NEWABYSS_OPENGLUTILS_CPP
#define NEWABYSS_OPENGLUTILS_CPP

class TextureUtils {

protected:
    static inline unsigned int abyssLogoSmall = 0;
    static inline bool alrLoaded = false;

public:
    static void unLoadTextures();
    static void renderAbyssLogo(float width, float height);
    static unsigned int loadTextureFromPNGArray(const unsigned char *pngData, int dataSize);
    static unsigned int loadTextureFromFile(const char *filename);

    static void startScale(float value);
    static void stopScale();

};

#endif //NEWABYSS_OPENGLUTILS_CPP