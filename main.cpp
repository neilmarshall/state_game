/*
The aim of this program is to require users to name a US state that
begins with a specified letter.
*/

#include "game.h"

int main()
{
    Game* game = new Game();  // instantiate Game object
    game->run();  // run game
    delete game;

    return 0;
}
