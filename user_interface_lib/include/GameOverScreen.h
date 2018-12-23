#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <ncurses.h>

// TODO add base class for MainMenu and GameOverScreen classes
class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	WINDOW * getWin() const;

private:
	WINDOW * win;

    int menu_h;
    int menu_w;

    int position_y;
    int position_x;

    void setPosition();
};

#endif // GAME_OVER_SCREEN_H
