#pragma once
#include "Component.h"
#include <SpriteGO.h>

class Animation : public Component
{
protected:
	bool isPlaying = false;

	float speed = 1.0f;
	AnimationClip* clip = nullptr;
	int currentFrame = -1;
	int totalFrame = 0;
	float clipFrameTime = 0.0f;
	float accumTime = 0.0f;

	sf::Sprite* target = nullptr;
public:
	Animation(SpriteGO& spriteGO);
	virtual ~Animation();
	void SetClip(AnimationClip* newClip);
	void SetSprite(sf::Sprite* sprite) { target = sprite; }
	sf::Sprite* GetSprite() const { return target; }
	bool IsPlaying() { return isPlaying; }
	void SetSpeed(float s) { speed = s; }
	float GetSpeed() const { return speed; }


	void Play(int frame = 0);
	void Seek(int frame);
	void Stop();

	float GetClipDuration();
	std::string GetClipName();

	void SetFrame(const AnimationFrame& frame);

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Reset() override {};
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGameObjectEnable() override {};
	virtual void OnGameObjectDisable() override {};
};

