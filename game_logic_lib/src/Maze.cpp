#include "Maze.h"

#include <iostream>
#include <fstream>
#include <exception>
// #include <ncurses.h>

Maze::Maze() : field_h(0), field_w(0), field(nullptr),
                                dotNumber(0), pacmanStart(0, 0),
                                ghostSpawn(0, 0), ghostStart(0, 0)
{
    vecStr strMap;

    if (!readMapFile(strMap))
    {
        std::cerr << "Map-file open failed. Try to place binary in project directory." <<  std::endl;
        exit(1);
    }

    // poor validation, main aspects only
    if (!interpretAndValidateMap(strMap))
    {
        std::cerr << "Map is not valid." << std::endl;
        exit(1);
    }

    std::cout << "Constructor Maze" << std::endl;
}

Maze::~Maze()
{
    for(int i = 0; i < field_h; ++i)
    {
        delete [] field[i];
    }
    delete [] field;
    std::cout << "Destructor Maze" << std::endl;
}

bool Maze::readMapFile(vecStr & sm)
{
    std::ifstream ifs("../maps/map2.map");
    if (!ifs.good())
    {
        ifs.open("./maps/map2.map");
        if (!ifs.good())
        {
            return false;
        }
    }
    std::string temp;
    while(ifs.good())
    {
        std::getline(ifs, temp);
        if (temp.size() != 0 && temp[0] != '#')
        {
            // copy to vector
            sm.push_back(temp);
        }
    }
    ifs.close();
    return true;
}

bool Maze::interpretAndValidateMap(vecStr & sm)
{
    if (sm.size() < 3)
        return false;

    try {
        field_h = std::stoi(sm[0]);
        field_w = std::stoi(sm[1]);
    } catch (std::exception &) {
        return false;
    }

    if (field_h < 1 || field_h > 1000 || field_w < 1 || field_w > 1000 ||
        sm.size() != static_cast<size_t>(field_h + 2))
        return false;

    sm.erase(sm.begin(), sm.begin() + 2);
    size_t temp_f_w = static_cast<size_t>(field_w);
    for (const auto & s : sm)
    {
        if (s.size() != temp_f_w)
            return false;
    }

    // memoty allocation for field member attribute.
    // allocation error is unlikely, so let it be wrong error message this time
    if (!(field = new (std::nothrow) char*[field_h]))
        return false;
    for(int i = 0; i < field_h; ++i)
    {
        if (!(field[i] = new (std::nothrow) char[field_w]))
            return false;
    }

    int pacmanCounter{0};
    int doorCounter{0};
    for(int i = 0; i < field_h; ++i)
    {
        for(int j = 0; j < field_w; ++j)
        {
            char c = sm[i][j];
            if (c == 'X' || c == ' ')
                ;
            else if (c == '.' || c == 'o')
                ++dotNumber;
            else if (c == 'P')
            {
                pacmanStart = pairInt(i, j);
                ++pacmanCounter;
            }
            else if (c == '_')
            {
                if (i == 0 || i == field_h - 1 ||
                    (sm[i - 1][j] != ' ') || (sm[i + 1][j] != ' '))
                    return false;
                ghostSpawn = pairInt(i + 1, j);
                ghostStart = pairInt(i - 1, j);
                ++doorCounter;
            }
            else
                return false;

            field[i][j] = sm[i][j];
        }
    }

    if (dotNumber < 1 || pacmanCounter != 1 || doorCounter != 1)
        return false;

    return true;
}

void Maze::reloadMap()
{
    for(int i = 0; i < field_h; ++i)
    {
        delete [] field[i];
    }
    delete [] field;

    dotNumber = 0;
    vecStr strMap;

    if (!readMapFile(strMap))
    {
        // invisible messaged due to ncurses mode
        std::cerr << "Map-file open failed." <<  std::endl;
        exit(1);
    }
    if (!interpretAndValidateMap(strMap))
    {
        std::cerr << "Map is not valid." << std::endl;
        exit(1);
    }
}

int Maze::getFieldHeight() const {
    return field_h;
}
int Maze::getFieldWidth() const {
    return field_w;
}
char ** Maze::getField() const {
    return field;
}

std::pair<int, int> Maze::getPacmanStart() const {
    return pacmanStart;
}
std::pair<int, int> Maze::getGhostSpawn() const {
    return ghostSpawn;
}
std::pair<int, int> Maze::getGhostStart() const {
    return ghostStart;
}

int Maze::getDotNumber() const {
    return dotNumber;
}

void Maze::decrementDotNumber()
{
    if (dotNumber > 0)
        --dotNumber;
}
