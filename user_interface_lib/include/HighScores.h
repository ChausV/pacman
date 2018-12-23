#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <map>
#include <string>

class HighScores
{
public:
	HighScores();
	~HighScores();

	std::multimap<int, std::string> & getContent();

	bool isHighScore(int score) const;
	void addHighScore(int score, std::string name);

private:
	std::multimap<int, std::string> content;
};

#endif // HIGH_SCORES_H
