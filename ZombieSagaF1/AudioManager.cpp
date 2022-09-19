#include "AudioManager.h"

void AudioManager::InitialiseAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void AudioManager::PlayCarSound()
{	
	result = system->playSound(engineSound, 0, false, &channel3);
	channel->setVolume(0.5);
}

void AudioManager::PlayBackgroundMusic()
{
	result = system->playSound(backgroundMusic, 0, false, &channel);
	channel->setVolume(0.1);
}

void AudioManager::PlayCollisionSound()
{
	result = system->playSound(crashSound, 0, false, &channel);
	channel->setVolume(0.1);
}

void AudioManager::LoadSounds()
{
	result = system->createSound("Assets/carSound.mp3", FMOD_DEFAULT, 0, &engineSound);
	result = engineSound->setMode(FMOD_LOOP_NORMAL);
	
	result = system->createStream("Assets/gameMusic.wav", FMOD_DEFAULT, 0, &backgroundMusic);
	// Allow the sound to be loopable
	result = backgroundMusic->setMode(FMOD_LOOP_NORMAL);
	// Set the sound to keep looping
	result = backgroundMusic->setLoopCount(-1);

	result = system->createSound("Assets/crashSound.mp3", FMOD_DEFAULT, 0, &crashSound);
	result = crashSound->setMode(FMOD_LOOP_OFF);
	
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

