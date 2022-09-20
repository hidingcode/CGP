#pragma once
#include "fmod.hpp"

class AudioManager
{
public:
	FMOD::System* system;
	FMOD::Sound* engineSound, * backgroundMusic, * crashSound;
	FMOD::Channel* channel = 0, * channel3 = 0;
	FMOD_RESULT	result;
	void* extradriverdata = 0;
	

	// Constructor
	AudioManager();
	// Destructor
	~AudioManager();
	
	void InitialiseAudio();
	void DynamicCarEngineSound(bool MoveForward, bool moveBackward);
	void PlayBackgroundMusic();
	void LoadSounds();
	void UpdateSound();
	void PlayCollisionSound();
	void ChangeState( bool pause);
	float DynamicSound(int windowWidth, int carPositionX);
	void StartCarEngineSound();
	
	
};