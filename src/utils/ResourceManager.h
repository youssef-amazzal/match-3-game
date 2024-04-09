#pragma once
#include "../headers/Header.h"

class ResourceManager {
private:
    ResourceManager() = default;
    static void loadSpriteSheets();
    static void loadSprites();

public:
    static std::map<SPRITES, SpriteSheet*> spriteSheets;

    static void loadTextures();
    static void loadAudio();
    static void loadFonts();
};



