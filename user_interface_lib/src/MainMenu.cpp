#include "MainMenu.h"

#include <iostream>

MainMenu::MainMenu() : win(nullptr), menu_h(25), menu_w(40),
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

	mvwprintw(win, 4, 15, "PACMAN");
	mvwprintw(win, 15, 16, "Controls:");
	mvwprintw(win, 16, 12, "Arrows to move");
	mvwprintw(win, 17, 15, "P - pause");
	mvwprintw(win, 18, 15, "Q - quit");
	mvwprintw(win, 23, 5, "by CHAUS (chausvm@gmail.com)");
	wrefresh(win);

}

MainMenu::~MainMenu()
{
	delwin(win);
    clear();
	endwin();
}

WINDOW * MainMenu::getWin() const {
	return win;
}

void MainMenu::setPosition()
{
    int terminal_h{0};
    int terminal_w{0};
    getmaxyx(stdscr, terminal_h, terminal_w);

    if (terminal_h < menu_h || terminal_w < menu_w)
    {
        endwin();
        std::cerr << "Terminal window is too small. Resize please" << std::endl;
        exit(-3);
    }
    position_y = (terminal_h - menu_h) / 2;
    position_x = (terminal_w - menu_w) / 2;
}
