#pragma once
#include "ShapeGameObj.h"
class RectangleShapeGO : public ShapeGameObj
{
public:
	RectangleShapeGO(const string& name = "");
	virtual void SetSize(const sf::Vector2f& size) override;
	virtual void SetRotation(const float& rotation) override;
};

