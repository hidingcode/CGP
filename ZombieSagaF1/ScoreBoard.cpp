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

string ScoreBoard::DisplayScore()
{	
	string scoreInString = "Score: " + to_string(score);
	return scoreInString;
}

