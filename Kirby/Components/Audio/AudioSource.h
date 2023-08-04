#pragma once
#include "Component.h"
#include <AudioGroup.h>
class AudioSource : public Component
{
protected:
	sf::SoundBuffer* soundClip = nullptr;
	sf::Sound soundStream;
	AudioGroup* audioGroup = nullptr;

	float volume = 100.0f;
	
public:
	AudioSource(GameObject& gameObject);
	virtual ~AudioSource();
	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Reset() override {};
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Release() override;

	void SetClip(sf::SoundBuffer* soundClip);

	void Play();
	void Stop();

	bool IsPlaying();

	void SetVolume(float volume);
	void SetLoop(bool isLoop);

	void OnAudioGroupVolumeChange();

	// Component을(를) 통해 상속됨
	virtual void OnGameObjectEnable() override;
	virtual void OnGameObjectDisable() override;
};