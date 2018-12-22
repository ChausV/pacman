#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

class Display
{
public:
    Display(int field_h, int field_w);
    // Display();
    ~Display();

    void setFieldSize(int field_h, int field_w);

    int getUserInput() const;

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
};

#endif // DISPLAY_H
