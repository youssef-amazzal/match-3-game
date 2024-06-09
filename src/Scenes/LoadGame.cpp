#include "LoadGame.h"
#include "../utils/FileManager.h"

void LoadGame::enter() {
    NewGame::enter();
    previewer->clear();
    auto j = FileManager::readJson(GAMESAVE_PATH / "save_file.json");
    deserialze(j);
}