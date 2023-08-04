#pragma once
#include "RectangleShapeGO.h"
class Door : public RectangleShapeGO
{
protected:
	sf::Vector2f movePosition;

public:
	const sf::Vector2f& GetMovePosition() const { return movePosition; }
};

