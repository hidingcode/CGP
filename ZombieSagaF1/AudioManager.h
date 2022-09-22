#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "fmod.hpp"

class AudioManager
{
public:
	FMOD::System* system;
	FMOD::Sound* engineSound, * backgroundMusic, * crashSound;
	FMOD::Channel* channel = 0,* channel2 = 0, * channel3 = 0;
	FMOD_RESULT	result;
	void* extradriverdata = 0;
	
	// Constructor
	AudioManager();
	// Destructor
	~AudioManager();
	
	void InitialiseAudio();
	void PlayCarEngineSound();
	void PlayBackgroundMusic();
	void LoadSounds();
	void UpdateSound();
	void PlayCollisionSound();
	// Change the State of the Sound to oause or un pause
	void ChangeSoundState(bool state);
	// Change the state of sound when the car moving and stop
	void ManageCarEngineSound(bool moveForward, bool moveBackward);
	// Pan the sound according to the  car (F1) position
	void DynamicCarEngineSound(int windowWidth, int carPositionX);
	
};
#endif