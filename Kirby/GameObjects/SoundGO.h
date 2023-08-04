#pragma once
#include "stdafx.h"
#include <ResourceManager.h>
#include "GameObject.h"

class SoundGO : public GameObject
{
protected:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string soundID;

	float volume = 100.f;
	bool isLooping = false;

public:
	SoundGO(const std::string& soundID = "", const std::string& name = "");
	virtual ~SoundGO();

	bool PlayCheck() const;
	
	void Play();
	void Stop();
	void Loop(bool loop);

	void SetVolume(float volume);
	float GetVolume() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};
