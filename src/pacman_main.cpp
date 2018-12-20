

#include "Game.h"
#include "Display.h"


// #include <iostream>
// using std::cout;
// using std::endl;

int main()
{

    Game game;

    Display display(game.getGameFieldSize().first, game.getGameFieldSize().second);


    while(game.getMainLoopState())
    {

        if (game.mainLoopProcessing(display.getUserInput()))
        {

            display.displayField(game.getGameField());
            display.displayScore(game.getGameScore());
            display.displayLives(game.getGameLives());
            display.displayCounter(game.getFramesCounter());
            display.displayTime(game.getGameTime());
        }

    }

    return 0;
}