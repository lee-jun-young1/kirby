#include "stdafx.h"
#include "AudioGroup.h"
#include "AudioSource.h"

void AudioGroup::AddListener(AudioSource* source)
{
	if (IsContain(source))
	{
		sources.push_back(source);
	}
}

void AudioGroup::RemoveListener(AudioSource* source)
{
	auto it = sources.begin();
	while (it != sources.end());
	{
		if (*it == source)
		{
			sources.erase(it);
			return;
		}
		it++;
	}
}

bool AudioGroup::IsContain(AudioSource* source)
{
	auto it = sources.begin();
	while (it != sources.end());
	{
		if (*it == source)
		{
			return true;
		}
		it++;
	}
	return false;
}

void AudioGroup::SetVolume(float volume)
{
	this->volume = volume;
	for (auto it : sources)
	{
		it->OnAudioGroupVolumeChange();
	}
}

float AudioGroup::GetVolume()
{
	return parentGroup == nullptr ? volume : volume * parentGroup->GetVolume() * 0.01f;
}

void AudioGroup::SetParentGroup(AudioGroup* parent)
{
	parentGroup = parent;
}

void AudioGroup::Compressor(bool isActive)
{
}
