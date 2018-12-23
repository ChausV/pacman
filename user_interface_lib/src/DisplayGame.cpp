#include "DisplayGame.h"

#include <iostream>

DisplayGame::DisplayGame(int field_h, int field_w)
     : win(nullptr), game_field_h(field_h), game_field_w(field_w),
        win_position_y(0), win_position_x(0)
{
    std::cout << "Constructor DisplayGame" << std::endl;

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
    setWindowPosition();
    win = newwin(field_h + 2, 2 * field_w + 2, win_position_y, win_position_x);
    box(win, 0, 0);
    wrefresh(win);

}

DisplayGame::~DisplayGame()
{
    delwin(win);
    // about not freed memory in ncurses:
    // https://stackoverflow.com/questions/32410125/valgrind-shows-memory-leaks-from-ncurses-commands-after-using-appropriate-free
    // nc_free_and_exit();
    clear();
    endwin();

    std::cout << "Destructor DisplayGame" << std::endl;
}

void DisplayGame::setWindowPosition()
{
    int terminal_h{0};
    int terminal_w{0};
    getmaxyx(stdscr, terminal_h, terminal_w);

    if (terminal_h < game_field_h + 4 || terminal_w < game_field_w * 2)
    {
        endwin();
        std::cerr << "Terminal window is too small. Resize please" << std::endl;
        exit(-2);
    }
    win_position_y = (terminal_h - (game_field_h + 4)) / 2 + 1;
    win_position_x = (terminal_w - (game_field_w) * 2) / 2;

}

void DisplayGame::setFieldSize(int field_h, int field_w)
{
    if (game_field_h == field_h && game_field_w == field_w)
        return ;

    game_field_h = field_h;
    game_field_w = field_w;

    delwin(win);
    clear();
    setWindowPosition();
    win = newwin(field_h + 2, 2 * field_w + 2, win_position_y, win_position_x);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
}

// not handled inscriptions overlapping for small maps
void DisplayGame::displayCounter(unsigned counter) const
{
    mvprintw(win_position_y - 1, win_position_x + 1, "Frames: %d", counter);
    refresh();
}

void DisplayGame::displayScore(int score) const
{
    mvprintw(win_position_y - 1, win_position_x + game_field_w - 5, "Score: %d", score);
    refresh();
}

void DisplayGame::displayLevel(int level) const
{
    mvprintw(win_position_y - 1, win_position_x + (2 * game_field_w) - 8, "Level: %d", level);
    refresh();
}

void DisplayGame::displayLives(int lives) const
{
    mvprintw(win_position_y + game_field_h + 2, win_position_x + 1, "Lives: %d", lives);
    refresh();
}

void DisplayGame::displayTime(float time) const
{
    mvprintw(win_position_y + game_field_h + 2, win_position_x + (2 * game_field_w) - 20,
                                                                "time: %.2f seconds", time);
    refresh();
}

void DisplayGame::displayField(char ** field) const
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
            else if (field[i][j] == 'G')
            {
                mvwaddch(win, i + 1, 2 * j + 1, 'O' | COLOR_PAIR(1));
                mvwaddch(win, i + 1, 2 * j + 2, 'O' | COLOR_PAIR(1));
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
