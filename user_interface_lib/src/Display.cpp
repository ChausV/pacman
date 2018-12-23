#include "Display.h"
#include "MainMenu.h"
#include "GameOverScreen.h"

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

bool Display::mainMenu()
{
    MainMenu mainMenu;

    WINDOW * menuWin = mainMenu.getWin();

    int     selector = 1;
    while(1)
    {
        if (selector % 2 == 0)
        {
            mvwprintw(menuWin, 10, 16, "  PLAY  ");
            wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, 12, 16, "  EXIT  ");
            wattroff(menuWin, A_REVERSE);
            wrefresh(menuWin);

        }
        else
        {
            wattron(menuWin, A_REVERSE); 
            mvwprintw(menuWin, 10, 16, "  PLAY  ");
            wattroff(menuWin, A_REVERSE); 
            mvwprintw(menuWin, 12, 16, "  EXIT  ");
            wrefresh(menuWin);
        }
        switch (getch())
        {
            case KEY_UP:
                selector++;
                break;
            case KEY_DOWN:
                selector++;
                break;
            case 10:
                delwin(menuWin);
                endwin();   
                return (selector % 2);
            default:
                mvwprintw(menuWin, 20, 5, "Up and down arrows to choose");
                mvwprintw(menuWin, 21, 10, "Enter to submit");
                wrefresh(menuWin);
                break;
        }
    }
    return true;

}

void Display::gameOverFrame(int score)
{
    GameOverScreen goScreen;

    WINDOW * goWin = goScreen.getWin();

    mvwprintw(goWin, 12, 12, "Your score: %d", score);
    mvwprintw(goWin, 14, 15, "press any key");
    wrefresh(goWin);

    getch();

}
