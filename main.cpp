

#include "Game.h"
#include "Maze.h"
#include "Display.h"

#include <iostream>

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
	unsigned counter = 0;
	bool loop_flag = true;
	while(loop_flag)
	{
		switch(input = getch())
		{

			case 'q':
				loop_flag = false;
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
		display.displayField(field);
		display.displayScore(game.getGameScore());
		display.displayCounter(++counter);
	}

	// getch();

	return 0;
}