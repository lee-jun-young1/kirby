#pragma once
#include "SpriteGO.h"
class KirbyEffect : public SpriteGO
{
private:
	float time;
	float duration;
	float speed;
	int targetAlpha;
public:
	KirbyEffect(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {}

	void StarShot(const float& direction);
	void EmptyShot(const float& direction);
	virtual void Update(float dt) override;

	virtual void OnTriggerEnter(Collider* col) override;
};

