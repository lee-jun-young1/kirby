#include "stdafx.h"
#include "RectangleShapeGO.h"


RectangleShapeGO::RectangleShapeGO(const string& name)
	:ShapeGameObj(ShapeType::Rectangle, name)
{
}

void RectangleShapeGO::SetSize(sf::Vector2f size)
{
	((sf::RectangleShape*)shape)->setSize(size);
}

sf::Vector2f RectangleShapeGO::GetSize()
{
	return ((sf::RectangleShape*)shape)->getSize();
}