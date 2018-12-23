#include "Display.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "HighScores.h"

#include <iostream>
#include <map>
#include <cctype>
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

void Display::showHighScores(WINDOW * win) const
{
    HighScores hs;

    for (int i = 2; i < 22; ++i)
    {
        for (int j = 5; j < 35; ++j)
        {
            mvwaddch(win, i, j, ' ');
        }
    }
    mvwprintw(win, 5, 15, "High scores:");

    std::multimap<int, std::string> & content = hs.getContent();
    std::multimap<int, std::string>::iterator it;
    std::multimap<int, std::string>::iterator end = content.end();
    int i;
    for (i = 10, it = content.begin(); it != end; ++it, --i)
    {
        mvwprintw(win, i + 7, 12, "%s", (*it).second.c_str());
        mvwprintw(win, i + 7, 25, "%d", (*it).first);
    }

    wrefresh(win);

    getch();
}

bool Display::mainMenu()
{
    MainMenu mainMenu;

    WINDOW * menuWin = mainMenu.getWin();

    int     selector = 1;
    while(1)
    {
        if (selector % 3 == 1)
        {
            wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, 8, 16, "     PLAY      ");
            wattroff(menuWin, A_REVERSE); 
        }
        else
        {
            mvwprintw(menuWin, 8, 16, "     PLAY      ");
        }
        if (selector % 3 == 2)
        {
            wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, 10, 16, "  HIGH SCORES  ");
            wattroff(menuWin, A_REVERSE); 
        }
        else
        {
            mvwprintw(menuWin, 10, 16, "  HIGH SCORES  ");
        }
        if (selector % 3 == 0)
        {
            wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, 12, 16, "     EXIT      ");
            wattroff(menuWin, A_REVERSE); 
        }
        else
        {
            mvwprintw(menuWin, 12, 16, "     EXIT      ");
        }
        wrefresh(menuWin);

        switch (getch())
        {
            case KEY_UP:
                selector--;
                if (selector == 0)
                    selector = 3;
                break;
            case KEY_DOWN:
                selector++;
                break;
            case 10:
                if (selector % 3 == 2)
                {
                    showHighScores(menuWin);
                    wclear(menuWin);
                    // refresh();
                    mainMenu.refreshMenuScreen();
                    // wrefresh(menuWin);
                }
                else
                {
                    delwin(menuWin);
                    endwin();
                    return (selector % 3 == 1) ? true : false;
                }
                break;
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
    HighScores hs;

    WINDOW * goWin = goScreen.getWin();

    mvwprintw(goWin, 12, 12, "Your score: %d", score);
    wrefresh(goWin);

    if (hs.isHighScore(score))
    {
        mvwprintw(goWin, 14, 10, "This is high score!");
        mvwprintw(goWin, 16, 10, "Enter your name here");
        mvwprintw(goWin, 17, 5, "(up to 10 graphical characters)");
        mvwprintw(goWin, 21, 15, "__________");
        wrefresh(goWin);

        std::string buffer{""};
        int input;
        int i = 0;
        while(1)
        {
            input = getch();
            if (isgraph(input))
            {
                buffer.append(1, input);
                mvwprintw(goWin, 21, i + 15, "%c", input);
                wrefresh(goWin);
                ++i;
            }
            else if (input == 10 && buffer.size())
            {
                break;
            }
            if (buffer.size() == 10)
            {
                break;
            }
        }
        hs.addHighScore(score, buffer);
    }
    else
    {
        mvwprintw(goWin, 17, 15, "press any key");
        wrefresh(goWin);

        getch();
    }
}
