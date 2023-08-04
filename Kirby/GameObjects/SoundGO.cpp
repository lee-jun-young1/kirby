#include "stdafx.h"
#include "SoundGO.h"
#include <Utils.h>
#include <ResourceManager.h>

SoundGO::SoundGO(const std::string& soundID, const std::string& name)
    :GameObject(name), soundID(soundID)
{
}

SoundGO::~SoundGO()
{
}

bool SoundGO::PlayCheck() const
{
	return sound.getStatus() == sf::Sound::Playing;
}

void SoundGO::Play()
{
	sound.play();
}

void SoundGO::Stop()
{
	sound.stop();
}

void SoundGO::Loop(bool loop)
{
	isLooping = loop;
}

void SoundGO::SetVolume(float volume)
{
	sound.setVolume(volume);
}

float SoundGO::GetVolume() const
{
	return sound.getVolume();
}

void SoundGO::Init()
{
}

void SoundGO::Release()
{
}

void SoundGO::Reset()
{
	sf::SoundBuffer* buffer = Resources.GetSoundBuffer(soundID);
	if (buffer != nullptr)
	{
		sound.setBuffer(*buffer);
	}
}

void SoundGO::Update(float dt)
{
	if (isLooping && sound.getStatus() == sf::Sound::Stopped)
	{
		sound.play();
	}
}

void SoundGO::Draw(sf::RenderWindow& window)
{
}