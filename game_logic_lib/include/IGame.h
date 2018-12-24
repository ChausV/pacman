#ifndef I_GAME_H
#define I_GAME_H

#include <utility>

/*
** Provides interface for general game logic class (Game class in this case).
*/
class IGame
{
public:
    virtual ~IGame() {}

    /*
    ** Returns game field size. First is height, second is width.
    */
    virtual std::pair<int, int> getGameFieldSize() const = 0;

    /*
    ** Returns pointer to array of char arrays, which represents game field (pacman's maze).
    ** Size of outer array is game field height (first from getGameFieldSize()).
    ** Size of inner arrays is game field width (second from getGameFieldSize()).
    ** Possible values of char elements:
    ** 'X' - maze wall,
    ** ' ' - empty place,
    ** '.' - dot (pacman's food),
    ** 'o' - energizer or cookie (eaten by pacman turns ghosts into scare mode),
    ** 'P' - current Pacman position,
    ** 'B' - current Blinky ghost position,
    ** 'S' - current Speedy ghost position,
    ** 'I' - current Inky ghost position,
    ** 'C' - current Clyde ghost position,
    ** 'G' - ghost in scare mode position,
    ** '_' - ghosts lair door.
    */ 
    virtual char ** getGameField() const = 0;

    /*
    ** Returns current game state.
    ** false if game is over, true othervise.
    */
    virtual bool getMainLoopState() const = 0;

    /*
    ** Returns current player's score.
    */
    virtual int getGameScore() const = 0;

    /*
    ** Returns amount of frames from game start.
    ** Frame in this case is state of game field to be displayed.
    */
    virtual unsigned getFramesCounter() const = 0;

    /*
    ** Returns time from game beginning.
    */
    virtual float getGameTime() const = 0;

    /*
    ** Returns current player's lives.
    */
    virtual int getGameLives() const = 0;

    /*
    ** Returns current game level.
    */
    virtual int getGameLevel() const = 0;

    /*
    ** Takes keycode of user input (-1 in case of no input).
    ** Returns true if there are some changes in game state which
    ** need to be displayed, false othervise.
    */
    virtual bool mainLoopProcessing(int input) = 0;
};

#endif // I_GAME_H
