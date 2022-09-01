#pragma once
#include <Windows.h>  // problem

class FrameTimer
{
	public:
		void Init(int);
		int FramesToUpdate();
	private:
		LARGE_INTEGER timerFreq;
		LARGE_INTEGER timeNow;
		LARGE_INTEGER timePrevious;
		int requestedFPS;
		float intervalsPerFrame;
		float intervalsSinceLastUpdate;

};

