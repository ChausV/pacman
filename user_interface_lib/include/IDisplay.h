#ifndef I_DISPLAY_H
#define I_DISPLAY_H

/*
** Provides interface for general user interface class (Display class in this case).
*/
class IDisplay
{
public:
	virtual ~IDisplay() {}

	/*
	** Determines start of game displaying.
	** Takes game field height and game field width.
	*/
    virtual void startGameDisplay(int field_h, int field_w) = 0;

	/*
	** Determines end of game displaying.
	*/
    virtual void endGameDisplay() = 0;

	/*
	** Takes game field height and game field width.
	** For example, may be usefull in case of game field size changes.
	*/
    virtual void setGameFieldSize(int field_h, int field_w) = 0;

	/*
	** Returns keycode of user input.
	** Returns -1 in case of no input.
	*/
    virtual int getUserInput() const = 0;

	/*
	** Displays game field.
	** See description of getGameField() in IGame class.
	*/
    virtual void displayGameField(char ** field) const = 0;

	/*
	** Displays player's score.
	*/
    virtual void displayScore(int score) const = 0;

	/*
	** Displays player's lives.
	*/
    virtual void displayLives(int lives) const = 0;

	/*
	** Displays game frames counter.
	*/
    virtual void displayCounter(unsigned counter) const = 0;

	/*
	** Displays time from game start (precision .2 is good enough in this case).
	*/
    virtual void displayTime(float time) const = 0;

	/*
	** Displays current level number.
	*/
    virtual void displayLevel(int level) const = 0;

	/*
	** Interacts with user.
	** Returns true if user wants to play game.
	** Returns false if user wants to exit.
	*/
    virtual bool mainMenu() = 0;

	/*
	** Informs user that the game is over.
	** Displays user's score.
	*/
    virtual void gameOverFrame(int score) = 0;
};

#endif // I_DISPLAY_H
