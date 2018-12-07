#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

class Display
{
public:
	Display(int field_h, int field_w);
	~Display();

	void displayField(char ** field) const;
private:
	WINDOW * win;

	int game_field_h;
	int game_field_w;
};

#endif // DISPLAY_H
