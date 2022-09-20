#include "AudioManager.h"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::InitialiseAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void AudioManager::PlayCarEngineSound()
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

void AudioManager::ChangeSoundState(bool state)
{
	//pause the music
	result = channel3->setPaused(state);

	//resume the music
	result = channel3->setPaused(state);
}

void AudioManager::ManageCarEngineSound(bool moveForward, bool moveBackward)
{	
	if (moveForward == true || moveBackward == true)
	{
		this->ChangeSoundState(false);
	}

	else
	{
		this->ChangeSoundState(true);
	}
}

void AudioManager::DynamicCarEngineSound(int windowWidth, int carPositionX)
{
	float halfWidth = windowWidth / 2;
	
	// If the car position is lower than half width
	if (carPositionX < halfWidth)
	{	
		// Pan the sound to left
		channel3->setPan(-(1 - (carPositionX/ halfWidth)));
	}

	else if (carPositionX == halfWidth)
	{
		channel3->setPan(0);
	}

	else if (carPositionX >= halfWidth)
	{
		channel3->setPan((carPositionX - halfWidth) / halfWidth);
	}	
}

