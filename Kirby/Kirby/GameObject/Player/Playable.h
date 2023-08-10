#pragma once
#include "SpriteGO.h"
class Playable : public SpriteGO
{
protected:
public:
	Playable(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {};
	virtual void Move(const sf::Vector2f& axis, const float& deltaTime) = 0;
	virtual void Dash(const sf::Vector2f& axis, const float& deltaTime) = 0;
	virtual void Charge() = 0;
	virtual void ChargeEnd() = 0;
};

