#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "GameHeader.h"

class ScoreBoard 
{
public:
	ScoreBoard();
	~ScoreBoard();

	void IncreaseScore(int score);
	int GetScore();
	string DisplayScore();

private:
	int score = 0;
	string scoreInString;
};
#endif