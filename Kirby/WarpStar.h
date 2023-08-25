#pragma once
#include "SpriteGO.h"
class WarpStar :
    public SpriteGO
{
protected:
	sf::Vector2f movePosition;

public:
	WarpStar(const std::string textureID = "sprites/effects/WarpStar.png", const std::string& name = "WarpStar") :SpriteGO(textureID, name) {}
	void SetMovePosition(const sf::Vector2f& movePosition) { this->movePosition = movePosition; }
	const sf::Vector2f& GetMovePosition() const { return movePosition; }

	virtual void Reset() override;
	void OnEnable();
};