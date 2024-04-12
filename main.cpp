#include "src/Game.h"

int main() {
    Game& Game = Game::getInstance();
    Game.init();
    Game.run();
    Game.exit();
    return 0;
}
