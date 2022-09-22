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

int ScoreBoard::GetScore()
{
	return score;
}

string ScoreBoard::DisplayScore()
{	
	scoreInString = "Score: " + to_string(score);
	return scoreInString;
}

