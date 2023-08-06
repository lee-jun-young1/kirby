#include "stdafx.h"
#include "CircleShapeGO.h"

CircleShapeGO::CircleShapeGO()
	:ShapeGameObj(ShapeType::Circle)
{

}

void CircleShapeGO::SetRadius(const float& radius)
{
	((sf::CircleShape*)shape)->setRadius(radius);
	GameObject::SetSize({ radius * 2.0f, radius * 2.0f });
}

void CircleShapeGO::SetSize(const sf::Vector2f& size)
{
	float radius = max(size.x, size.y) * 0.5f;
	((sf::CircleShape*)shape)->setRadius(radius);
	GameObject::SetSize({ radius * 2.0f, radius * 2.0f });
}
