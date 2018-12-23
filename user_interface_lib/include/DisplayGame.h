#ifndef DISPLAY_GAME_H
#define DISPLAY_GAME_H

#include <ncurses.h>

class DisplayGame
{
public:
    DisplayGame(int field_h, int field_w);
    ~DisplayGame();

    void setFieldSize(int field_h, int field_w);

    void displayField(char ** field) const;
    void displayScore(int score) const;
    void displayLives(int lives) const;
    void displayCounter(unsigned counter) const;
    void displayTime(float time) const;
    void displayLevel(int level) const;
private:
    WINDOW * win;

    int game_field_h;
    int game_field_w;

    int win_position_y;
    int win_position_x;

    void setWindowPosition();
};

#endif // DISPLAY_GAME_H
