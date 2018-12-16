

#include "Game.h"
#include "Display.h"

#include <iostream>

#include <chrono>

using std::cout;
using std::endl;

int main()
{
    cout << "Hello" << endl;


    Game game;

    std::pair<int, int> fieldSize = game.getGameFieldSize();
    Display display(fieldSize.first, fieldSize.second);


    while(game.getMainLoopState())
    {

        if (game.mainLoopProcessing(display.getUserInput()))
        {

            display.displayField(game.getGameField());
            display.displayScore(game.getGameScore());
            display.displayCounter(game.getFramesCounter());
            display.displayTime(game.getGameTime());
        }

    }

    return 0;
}