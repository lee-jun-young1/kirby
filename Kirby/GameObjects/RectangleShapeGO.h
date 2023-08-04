#pragma once
#include "ShapeGameObj.h"
class RectangleShapeGO : public ShapeGameObj
{
public:
	RectangleShapeGO(const string& name = "");
	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize();
};

