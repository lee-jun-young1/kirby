#pragma once
#include "ShapeGameObj.h"
class RectangleShapeGO : public ShapeGameObj
{
protected:
	std::string textureId;
public:
	RectangleShapeGO(const string& name = "");
	virtual void SetSize(const sf::Vector2f& size) override;
	virtual void SetRotation(const float& rotation) override;

	void SetTexture(const string& textrueId);
	void SetTextureRect(const sf::IntRect& rect);

	virtual void Reset() override;
};

