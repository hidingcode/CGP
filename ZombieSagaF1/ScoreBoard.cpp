#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::~ScoreBoard()
{

}

void ScoreBoard::IncreaseScore(int score)
{
	this->score += score;
}

LPCSTR ScoreBoard::DisplayScore()
{	
	string scoreInString = "Score: " + to_string(score);
	LPCSTR scoreInLPCSTR = scoreInString.c_str();

	return scoreInLPCSTR;
}
