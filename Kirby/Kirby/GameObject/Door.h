#pragma once
#include "RectangleShapeGO.h"
#include "SpriteGO.h"

class Door : public SpriteGO
{
protected:
	DoorType doorType = DoorType::None;
	bool isRecycle = false;
	sf::Vector2f movePosition;

public:
	Door(const std::string textureID = "", const std::string& name = "");

	const DoorType& GetDoorType() const { return doorType; }
	void SetDoorType(const DoorType& type) { doorType = type; }

	const sf::Vector2f& GetMovePosition() const { return movePosition; }
	void SetMovePosition(const sf::Vector2f& position) { movePosition = position; }
};

