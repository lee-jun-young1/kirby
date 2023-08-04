#include "stdafx.h"
#include "AudioSource.h"

AudioSource::AudioSource(GameObject& gameObject)
	:Component(gameObject, ComponentType::Audio, false)
{
}

AudioSource::~AudioSource()
{
}

void AudioSource::Init()
{
}

void AudioSource::Update(float deltaTime)
{
}

void AudioSource::Draw(sf::RenderWindow& window)
{
}

void AudioSource::Release()
{
}

void AudioSource::SetClip(sf::SoundBuffer* soundClip)
{
	this->soundClip = soundClip;
	soundStream.setBuffer(*soundClip);
 }

void AudioSource::Play()
{
	soundStream.play();
}

void AudioSource::Stop()
{
	soundStream.stop();
}

bool AudioSource::IsPlaying()
{
	return soundStream.getStatus() == sf::SoundSource::Playing;
}

void AudioSource::SetVolume(float volume)
{
	this->volume = volume;
	if (audioGroup != nullptr)
	{
		volume *= audioGroup->GetVolume() * 0.01f;
	}
	soundStream.setVolume(volume);
}

void AudioSource::SetLoop(bool isLoop)
{
	soundStream.setLoop(isLoop);
}

void AudioSource::OnAudioGroupVolumeChange()
{
	soundStream.setVolume(volume * audioGroup->GetVolume() * 0.01f);
}

void AudioSource::OnGameObjectEnable()
{
}

void AudioSource::OnGameObjectDisable()
{
}
