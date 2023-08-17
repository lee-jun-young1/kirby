#pragma once
#include "SpriteGO.h"
class Door : public SpriteGO
{
protected:
	sf::Vector2f movePosition;

public:
	Door(const std::string textureID = "", const std::string& name = "") :SpriteGO(textureID, name) {}
	void SetMovePosition(const sf::Vector2f& movePosition) { this->movePosition = movePosition; }
	const sf::Vector2f& GetMovePosition() const { return movePosition; }
};

