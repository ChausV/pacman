#include "Display.h"

#include <iostream>

Display::Display(int field_h, int field_w) : game_field_h(field_h),
											game_field_w(field_w)
{
	std::cout << "Constructor Display" << std::endl;

	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLUE);
	refresh();

	win = newwin(field_h + 2, 2 * field_w + 2, 5, 5);

	box(win, 0, 0);
	wrefresh(win);

}

Display::~Display()
{
	delwin(win);

	endwin();

	std::cout << "Destructor Display" << std::endl;
}

void Display::displayField(char ** field) const
{
	for(int i = 0; i < game_field_h; ++i)
	{
		for(int j = 0; j < game_field_w; ++j)
		{
			if (field[i][j] == 'X')
			{
				// wattron(win, COLOR_PAIR(1));
				// mvwprintw(win, i + 2, j + 2, " ");
				// wattroff(win, COLOR_PAIR(1));
				mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(1));
				mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(1));
			}
			if (field[i][j] == '.')
			{
				// wattron(win, COLOR_PAIR(1));
				// mvwprintw(win, i + 2, j + 2, " ");
				// wattroff(win, COLOR_PAIR(1));
				mvwaddch(win, i + 1, 2 * j + 1, '.');
				// mvwaddch(win, i + 1, 2 * j + 2, '.');
			}
		}
	}
	wrefresh(win);
}
