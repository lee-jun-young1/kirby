#pragma once
#include "RectangleShapeGO.h"
class Door : public RectangleShapeGO
{
protected:
	DoorType doorType;
	bool isRecycle = false;
	sf::Vector2f movePosition;

public:
	const sf::Vector2f& GetMovePosition() const { return movePosition; }
};

