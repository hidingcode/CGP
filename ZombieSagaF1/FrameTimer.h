#pragma once
#include <Windows.h>

class FrameTimer
{
public:
	// Initialise Timer
	void Init(int);
	int FramesToUpdate();
private:
	// Timer Frequent
	LARGE_INTEGER timerFreq;
	// Time Now
	LARGE_INTEGER timeNow;
	// Previous time
	LARGE_INTEGER timePrevious;
	int requestedFPS;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;

};