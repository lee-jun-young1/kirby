#include "stdafx.h"
#include "RectangleShapeGO.h"


RectangleShapeGO::RectangleShapeGO(const string& name)
	:ShapeGameObj(ShapeType::Rectangle, name)
{
}

void RectangleShapeGO::SetSize(const sf::Vector2f& size)
{
	((sf::RectangleShape*)shape)->setSize(size);
	GameObject::SetSize(size);
}