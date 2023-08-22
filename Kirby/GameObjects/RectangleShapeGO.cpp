#include "stdafx.h"
#include "RectangleShapeGO.h"
#include "ResourceManager.h"


RectangleShapeGO::RectangleShapeGO(const string& name)
	:ShapeGameObj(ShapeType::Rectangle, name)
{
}

void RectangleShapeGO::SetSize(const sf::Vector2f& size)
{
	((sf::RectangleShape*)shape)->setSize(size);
	GameObject::SetSize(size);
}

void RectangleShapeGO::SetRotation(const float& rotation)
{
	GameObject::SetRotation(rotation);
	((sf::RectangleShape*)shape)->setRotation(rotation);
}

void RectangleShapeGO::SetTexture(const string& textureId)
{
	this->textureId = textureId;
}

void RectangleShapeGO::SetTextureRect(const sf::IntRect& rect)
{
	((sf::RectangleShape*)shape)->setTextureRect(rect);
}

void RectangleShapeGO::Reset()
{
	GameObject::Reset(); 
	sf::Texture* tex = Resources.GetTexture(textureId);
	if (tex != nullptr)
	{
		((sf::RectangleShape*)shape)->setTexture(tex);
	}
}
