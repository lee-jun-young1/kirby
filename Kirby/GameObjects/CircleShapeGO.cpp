#include "stdafx.h"
#include "CircleShapeGO.h"

CircleShapeGO::CircleShapeGO()
	:ShapeGameObj(ShapeType::Circle)
{

}

void CircleShapeGO::SetSize(const float& radius)
{
	((sf::CircleShape*)shape)->setRadius(radius);
}
