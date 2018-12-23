

#include "Game.h"
#include "Display.h"


// #include <random>

// #include <iostream>
// using std::cout;
// using std::endl;

int main()
{

    Display display;

    while(display.mainMenu())
    {
        Game game;
        display.startGameDisplay(game.getGameFieldSize().first, game.getGameFieldSize().second);

        while(game.getMainLoopState())
        {
            if (game.mainLoopProcessing(display.getUserInput()))
            {
                display.setGameFieldSize(game.getGameFieldSize().first, game.getGameFieldSize().second);

                display.displayGameField(game.getGameField());
                display.displayScore(game.getGameScore());
                display.displayLives(game.getGameLives());
                display.displayCounter(game.getFramesCounter());
                display.displayTime(game.getGameTime());
                display.displayLevel(game.getGameLevel());
            }
        }
        display.endGameDisplay();
        display.gameOverFrame(game.getGameScore());
    }

    return 0;
}