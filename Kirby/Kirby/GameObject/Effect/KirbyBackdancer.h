#pragma once
#include "SpriteGO.h"
class KirbyBackdancer : public SpriteGO
{
private:
	GameObject* kirby;
	sf::Vector2f offset;
public:
	KirbyBackdancer(const std::string textureID = "sprites/kirby/Class_Normal.png", const std::string& name = "KirbyBackDancer")
		:SpriteGO(textureID, name) {}
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetKirby(GameObject* kirby, sf::Vector2f offset) { this->kirby = kirby; this->offset = offset; }
};

