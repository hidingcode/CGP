#pragma once
#include "fmod.hpp"

class AudioManager
{
public:
	FMOD::System* system;
	FMOD::Sound* sound1, * sound2, * sound3;
	FMOD::Channel* channel = 0, * channel3 = 0;
	FMOD_RESULT	result;
	void* extradriverdata = 0;
	

	// Constructor
	AudioManager();
	// Destructor
	~AudioManager();
	
	void InitializeAudio();
	void PlayCarSound();
	void PlaySoundTrack();
	void LoadSounds();
	void UpdateSound();
	void PlayCollision();
	void ChangeState( bool pause);
	float DynamicSound(int windowWidth, int carPositionX);
	
	
};