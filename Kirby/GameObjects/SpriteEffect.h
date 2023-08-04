#pragma once
#include "SpriteGO.h"
#include "ObjectPool.h"
class SpriteEffect : public SpriteGO
{
protected:
	float inverseDuration = 0.0f;
	float duration = 0.0f;
	float timer = 0.0f;

	ObjectPool<SpriteEffect>* pool = nullptr;
public:
	SpriteEffect(const float& timer = 0.0f, const std::string textureID = "", const std::string& name = "");
	virtual ~SpriteEffect() override {};
	
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetDuration(float duration);
	void SetPool(ObjectPool<SpriteEffect>* pool) { this->pool = pool; }
};

