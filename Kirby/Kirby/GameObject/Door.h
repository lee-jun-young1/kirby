#pragma once
#include "RectangleShapeGO.h"
class Door : public RectangleShapeGO
{
protected:
	DoorType doorType;
	bool isRecycle = false;
	sf::Vector2f movePosition;

public:
	Door(const string& name = "");

	const DoorType& GetDoorType() const { return doorType; }
	void SetDoorType(const DoorType& type) { doorType = type; }

	const sf::Vector2f& GetMovePosition() const { return movePosition; }
	void SetMovePosition(const sf::Vector2f& position) { movePosition = position; }
};

