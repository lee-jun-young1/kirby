#include "stdafx.h"
#include "ShapeGameObj.h"
#include <Utils.h>

ShapeGameObj::ShapeGameObj(ShapeType shapeType, const string& name)
	:GameObject(name), type(shapeType)
{
	switch (type)
	{
	case ShapeType::None:
		//error
		break;
	case ShapeType::Circle:
		shape = new sf::CircleShape();
		break;
	case ShapeType::Convex:
		shape = new sf::ConvexShape();
		break;
	case ShapeType::Rectangle:
		shape = new sf::RectangleShape();
		break;
	}
}

void ShapeGameObj::Init()
{
}

void ShapeGameObj::Release()
{
	delete shape;
}

void ShapeGameObj::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void ShapeGameObj::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(*shape);
}

void ShapeGameObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(*shape, origin);
}

void ShapeGameObj::SetPosition(const sf::Vector2f& position)
{
	GameObject::SetPosition(position);
	shape->setPosition(position);
}

void ShapeGameObj::SetFillColor(sf::Color color)
{
	shape->setFillColor(color);
}

void ShapeGameObj::Reset()
{
	GameObject::Reset();
}
