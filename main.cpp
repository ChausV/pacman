

#include "Game.h"
#include "Display.h"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
	cout << "Hello" << endl;



	Game game;
	char ** field = game.getField();


	Display display(game.getFieldHeight(), game.getFieldWidth());


	display.displayField(field);

	getch();


	return 0;
}