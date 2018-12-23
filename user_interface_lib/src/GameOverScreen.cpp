#include "GameOverScreen.h"

#include <iostream>

GameOverScreen::GameOverScreen() : win(nullptr), menu_h(25), menu_w(40),
						position_y(0), position_x(0)
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, true);
	nodelay(stdscr, false);



	refresh();
	setPosition();
	win = newwin(menu_h, menu_w, position_y, position_x);
	box(win, 0, 0);
	wrefresh(win);

	mvwprintw(win, 4, 15, "GAME OVER");
	wrefresh(win);

}

GameOverScreen::~GameOverScreen()
{
	delwin(win);
    clear();
	endwin();
}

WINDOW * GameOverScreen::getWin() const {
	return win;
}

void GameOverScreen::setPosition()
{
    int terminal_h{0};
    int terminal_w{0};
    getmaxyx(stdscr, terminal_h, terminal_w);

    position_y = (terminal_h - menu_h) / 2;
    position_x = (terminal_w - menu_w) / 2;
}
