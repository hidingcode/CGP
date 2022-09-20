#include <d3dx9.h>
#include <string>

using namespace std;

class ScoreBoard 
{
public:
	ScoreBoard();
	~ScoreBoard();

	void IncreaseScore(int score);
	void UpdateScore();
	int GetScore();
	string DisplayScore();

private:
	int score = 0;
	LPCSTR scoreInLPCSTR;
};