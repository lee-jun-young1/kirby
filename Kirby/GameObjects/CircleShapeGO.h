#pragma once
#include "ShapeGameObj.h"
class CircleShapeGO : public ShapeGameObj
{
public:
	CircleShapeGO();
	void SetRadius(const float& radius);
	/// <summary>
	/// Set Radius (size's max value * 0.5f)
	/// </summary>
	virtual void SetSize(const sf::Vector2f& size) override;
};