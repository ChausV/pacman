#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <ncurses.h>

// TODO add base class for MainMenu and GameOverScreen classes
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	WINDOW * getWin() const;

	void refreshMenuScreen() const;

private:
	WINDOW * win;

    int menu_h;
    int menu_w;

    int position_y;
    int position_x;

    void setPosition();
};

#endif // MAIN_MENU_H