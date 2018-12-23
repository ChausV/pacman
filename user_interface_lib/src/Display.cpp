#include "Display.h"

#include <iostream>
#include <ncurses.h>

Display::Display()
     : displayGame(nullptr)
{
    std::cout << "Constructor Display" << std::endl;
}

Display::~Display()
{
    delete displayGame;     // just to be on the safe side

    std::cout << "Destructor Display" << std::endl;
}


int Display::getUserInput() const
{
    return getch();
}

void Display::startGameDisplay(int field_h, int field_w)
{
    if (displayGame == nullptr)
    {
        displayGame = new (std::nothrow) DisplayGame(field_h, field_w);
        if (displayGame == nullptr)
        {
            std::cerr << "memory allocation failed. exit() now" << std::endl;
            exit(-1);
        }
    }
}
void Display::endGameDisplay()
{
    delete displayGame;
    displayGame = nullptr;
}

void Display::setGameFieldSize(int field_h, int field_w) {
    displayGame->setFieldSize(field_h, field_w);
}
void Display::displayScore(int score) const {
    displayGame->displayScore(score);
}
void Display::displayLives(int lives) const {
    displayGame->displayLives(lives);
}
void Display::displayCounter(unsigned counter) const {
    displayGame->displayCounter(counter);
}
void Display::displayTime(float time) const {
    displayGame->displayTime(time);
}
void Display::displayLevel(int level) const {
    displayGame->displayLevel(level);
}
void Display::displayGameField(char ** field) const {
    displayGame->displayField(field);
}
