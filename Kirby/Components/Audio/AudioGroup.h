#pragma once

class AudioSource;

class AudioGroup
{
protected:
	std::list<AudioSource*> sources;
	AudioGroup* parentGroup;
	float volume = 100.0f;
public:
	void AddListener(AudioSource* source);
	void RemoveListener(AudioSource* source);

	bool IsContain(AudioSource* source);

	void SetVolume(float volume);
	float GetVolume();

	void SetParentGroup(AudioGroup* parent);
	void Compressor(bool isActive);
};

