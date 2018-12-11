#ifndef MAZE_HABITANT_H
#define MAZE_HABITANT_H

class MazeHabitant
{
public:
	MazeHabitant() = default;
	~MazeHabitant() = default;

	void setY(int y);
	void setX(int x);
	int getY() const;
	int getX() const;

private:
	int y;
	int x;
};

#endif // MAZE_HABITANT_H
