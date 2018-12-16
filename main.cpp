

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

    char ** field = game.getGameField();

    std::pair<int, int> fieldSize = game.getGameFieldSize();
    Display display(fieldSize.first, fieldSize.second);


    int input = 0;
    int input_2 = 0;
    unsigned counter = 0u;
    bool loop_flag = true;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;
    float delay = 0.0f;
    float diff;
    while(loop_flag)
    {

        input = getch();
        if (input != -1)
            input_2 = input;


        end = std::chrono::steady_clock::now();
        diff = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

        if (diff > delay)
        {

            switch(input_2)
            {
                case 'q':
                    loop_flag = false;
                    break;
                case 'p':
                    nodelay(stdscr, false);
                    while('p' != getch())
                        ;
                    nodelay(stdscr, true);
                    break;
                case KEY_LEFT:
                    game.pacmanLeft();
                    break;
                case KEY_RIGHT:
                    game.pacmanRight();
                    break;
                case KEY_UP:
                    game.pacmanUp();
                    break;
                case KEY_DOWN:
                    game.pacmanDown();
                    break;
            }
            input_2 = -1;

            game.processStep();

            display.displayField(field);
            display.displayScore(game.getGameScore());
            display.displayCounter(counter);
            ++counter;
            mvprintw(30, 30, "time: %f", diff);
            delay += 0.1f;
        }
    }

    // getch();

    return 0;
}