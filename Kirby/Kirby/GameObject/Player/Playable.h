#pragma once
#include "SpriteGO.h"
class Playable : public SpriteGO
{
protected:
public:
	Playable(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {};
	virtual void MoveKey(const sf::Vector2f& axis, const float& deltaTime) = 0;
	virtual void DashKey(const sf::Vector2f& axis, const float& deltaTime) = 0;
	virtual void MoveKeyEnd() = 0;
	virtual void ChargeKey() = 0;
	virtual void ChargeKeyContinue() = 0;
	virtual void ChargeKeyEnd() = 0;
	virtual void SitKey() = 0;
	virtual void SitKeyEnd() = 0;
	virtual void JumpKey() = 0;
	virtual void VKey() = 0;
};

