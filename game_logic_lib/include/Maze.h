#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <vector>
#include <utility>

class Maze
{
public:
    Maze();
    ~Maze();

    int getFieldHeight() const;
    int getFieldWidth() const;
    char ** getField() const;

    std::pair<int, int> getPacmanStart() const;
    std::pair<int, int> getGhostSpawn() const;
    std::pair<int, int> getGhostStart() const;

    int getDotNumber() const;
    void decrementDotNumber();

    void reloadMap(int level);

private:

    using vecStr = std::vector<std::string>;
    using pairInt = std::pair<int, int>;

    int field_h;
    int field_w;
    char ** field;

    int dotNumber;
    pairInt pacmanStart;
    pairInt ghostSpawn;
    pairInt ghostStart;

    bool readMapFile(vecStr & sm, int level);
    bool interpretAndValidateMap(vecStr & sm);

};

#endif // MAZE_H
