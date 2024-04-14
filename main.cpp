#include "src/GameCycle.h"

int main() {
    GameCycle& Game = GameCycle::getInstance();
    Game.init();
    Game.run();
    Game.exit();
    return 0;
}
