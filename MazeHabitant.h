#ifndef MAZE_HABITANT_H
#define MAZE_HABITANT_H

class MazeHabitant
{
public:
    MazeHabitant();
    ~MazeHabitant() = default;
    
    int getY() const;
    int getX() const;
    char getCurrDirection() const;
    char getNextDirection() const;

    void setY(int y);
    void setX(int x);
    void setCurrDirection(char c);
    void setNextDirection(char c);

private:
    int y;
    int x;
    char currentDirection;
    char nextDirection;
};

#endif // MAZE_HABITANT_H
