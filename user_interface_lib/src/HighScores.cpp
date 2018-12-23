#include "HighScores.h"

#include <fstream>
#include <iostream>
#include <ncurses.h>

HighScores::HighScores() : content()
{
	std::ifstream ifs;
	ifs.open("../highscores/highscores.hs");
	if (!ifs.good())
	{
		ifs.open("./highscores/highscores.hs");
		if (!ifs.good())
		{
	        endwin();
	        std::cerr << "Highscores file open filed" << std::endl;
	        exit(-4);
		}
	}

	// no highscore file validation this time. assuming no malicious changes in file.
	int tmpint{0};
	std::string tmpstr{""};
	for (int i = 0; i < 10; ++i)
	{
		ifs >> tmpint >> tmpstr;
		content.insert(std::pair<int, std::string>(tmpint, tmpstr));
	}
	ifs.close();
}

HighScores::~HighScores()
{}

std::multimap<int, std::string> & HighScores::getContent()
{
	return content;
}

bool HighScores::isHighScore(int score) const
{
	auto first = content.begin();
	return ((*first).first < score) ? true : false;
}

void HighScores::addHighScore(int score, std::string name)
{
	content.erase(content.begin());
	content.insert(std::pair<int, std::string>(score, name));

	std::ofstream ofs;
	ofs.open("../highscores/highscores.hs", std::ofstream::out | std::ofstream::trunc);
	if (!ofs.good())
	{
		ofs.open("./highscores/highscores.hs", std::ofstream::out | std::ofstream::trunc);
		if (!ofs.good())
		{
	        endwin();
	        std::cerr << "Highscores file open filed" << std::endl;
	        exit(-4);
		}
	}

    std::multimap<int, std::string>::iterator it;
    std::multimap<int, std::string>::iterator end = content.end();
    for (it = content.begin(); it != end; ++it)
    {
    	ofs << (*it).first << " " << (*it).second << std::endl;
    }

	ofs.close();
}
