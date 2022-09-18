#pragma once
#include "fmod.hpp"

class AudioManager
{
public:
	FMOD::System* system;
	FMOD::Sound* sound1, * sound2, * sound3;
	FMOD::Channel* channel = 0;
	FMOD_RESULT	result;
	void* extradriverdata = 0;

	void InitializeAudio();
	void PlaySound1();
	void PlaySoundTrack();
	void LoadSounds();
	void GetSoundLength();
	void UpdateSound();
	void PlayCollision();

	AudioManager();
	~AudioManager();
};