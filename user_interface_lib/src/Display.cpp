#include "Display.h"

#include <iostream>

Display::Display(int field_h, int field_w) : game_field_h(field_h),
                                            game_field_w(field_w)
{
    std::cout << "Constructor Display" << std::endl;

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);

    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);

    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    refresh();

    win = newwin(field_h + 2, 2 * field_w + 2, 5, 5);

    box(win, 0, 0);
    wrefresh(win);

}

Display::~Display()
{
    delwin(win);
    // about not freed memory in ncurses:
    // https://stackoverflow.com/questions/32410125/valgrind-shows-memory-leaks-from-ncurses-commands-after-using-appropriate-free
    // _nc_free_and_exit();
    endwin();

    std::cout << "Destructor Display" << std::endl;
}

int Display::getUserInput() const
{
    return getch();
}

void Display::displayScore(int score) const
{
    mvprintw(3, 25, "Score: %d", score);
    refresh();
}

void Display::displayLives(int lives) const
{
    mvprintw(30, 5, "Lives: %d", lives);
    refresh();
}

void Display::displayCounter(unsigned counter) const
{
    mvprintw(3, 5, "Counter: %d", counter);
    refresh();
}

void Display::displayTime(float time) const
{
    mvprintw(30, 30, "time: %f", time);
    refresh();
}

void Display::displayField(char ** field) const
{
    for(int i = 0; i < game_field_h; ++i)
    {
        for(int j = 0; j < game_field_w; ++j)
        {
            if (field[i][j] == 'X')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(1));
                mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(1));
            }
            else if (field[i][j] == '.')
            {
                mvwaddch(win, i + 1, 2 * j + 1, '.');
                mvwaddch(win, i + 1, 2 * j + 2, ' ');
            }
            else if (field[i][j] == 'o')
            {
                mvwaddch(win, i + 1, 2 * j + 1, 'o');
                mvwaddch(win, i + 1, 2 * j + 2, ' ');
            }
            else if (field[i][j] == 'P')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(2));
                mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(2));
            }
            else if (field[i][j] == 'B')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(3));
                mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(3));
            }
            else if (field[i][j] == 'S')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(4));
                mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(4));
            }
            else if (field[i][j] == 'I')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(7));
                mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(7));
            }
            else if (field[i][j] == 'C')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ' | COLOR_PAIR(6));
                mvwaddch(win, i + 1, 2 * j + 2, ' ' | COLOR_PAIR(6));
            }
            else if (field[i][j] == '_')
            {
                mvwaddch(win, i + 1, 2 * j + 1, '_');
                mvwaddch(win, i + 1, 2 * j + 2, '_');
            }
            else if (field[i][j] == ' ')
            {
                mvwaddch(win, i + 1, 2 * j + 1, ' ');
                mvwaddch(win, i + 1, 2 * j + 2, ' ');
            }
        }
    }
    wrefresh(win);
}
