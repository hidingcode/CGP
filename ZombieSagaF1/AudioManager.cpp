#include "AudioManager.h"

void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void AudioManager::PlayCarSound()
{	
	result = system->playSound(sound1, 0, false, &channel3);
	/*channel->setVolume(0);*/
}

void AudioManager::PlaySoundTrack()
{
	result = system->playSound(sound2, 0, false, &channel);
	channel->setVolume(0.1);
}

void AudioManager::PlayCollision()
{
	result = system->playSound(sound3, 0, false, &channel);
	channel->setVolume(0.1);
}

void AudioManager::LoadSounds()
{
	result = system->createSound("Assets/carSound.mp3", FMOD_DEFAULT, 0, &sound1);
	result = sound1->setMode(FMOD_LOOP_NORMAL);
	result = sound2->setLoopCount(-1);
	

	result = system->createStream("Assets/gameMusic.wav", FMOD_DEFAULT, 0, &sound2);
	// Allow the sound to be loopable
	result = sound2->setMode(FMOD_LOOP_NORMAL);
	// Set the sound to keep looping
	result = sound2->setLoopCount(-1);
	//FMOD_RESULT = result, sound = sound123, setLoopCount(-1)

	result = system->createSound("Assets/crashSound.mp3", FMOD_DEFAULT, 0, &sound3);
	result = sound3->setMode(FMOD_LOOP_OFF);
	
}

void AudioManager::UpdateSound()
{
	result = system->update();
}

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
}



void AudioManager::ChangeState(bool pause)
{
	if (pause == true)
	{
		//pause the music
		result = channel3->setPaused(true);
	}
	else
	{
		//resume the music
		result = channel3->setPaused(false);
	}

}

float AudioManager::DynamicSound(int windowWidth, int carPositionX)
{
	float halfWidth = windowWidth / 2;
	

	if (carPositionX < halfWidth)
	{
		channel3->setPan(-(1 - (carPositionX/ halfWidth)));
		return (-(1 - (carPositionX / halfWidth)));
	}

	else if (carPositionX == halfWidth)
	{
		channel3->setPan(0);
		return (0);
	}

	else if (carPositionX >= halfWidth)
	{
		channel3->setPan((carPositionX - halfWidth) / halfWidth);
		return ((carPositionX - halfWidth) / halfWidth);
	}

	
}

