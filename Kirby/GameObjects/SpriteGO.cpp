#include "stdafx.h"
#include "SpriteGO.h"
#include "Utils.h"

SpriteGO::SpriteGO(const std::string textureID, const std::string& name)
	:GameObject(name), textureID(textureID)
{
}

void SpriteGO::SetTexture(sf::Texture& texture, sf::Vector2f spriteDir)
{
	sprite.setTexture(texture);
	spriteDirection = spriteDir;
}

void SpriteGO::SetTextureID(const std::string textureID)
{
	this->textureID = textureID;
}

void SpriteGO::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
	sprite.setPosition(position);
}

void SpriteGO::SetPosition(const float& x, const float& y)
{
	this->position.x = x;
	this->position.y = y;
	sprite.setPosition(this->position);
}

void SpriteGO::SetOrigin(const Origins& origin)
{
	this->origin = Utils::SetOrigin(sprite, origin);
}

void SpriteGO::SetOrigin(const sf::Vector2f& origin)
{
	this->origin = origin;
	sprite.setOrigin(origin);
}

sf::Vector2f SpriteGO::GetOrigin() const
{
	return sprite.getOrigin();
}

sf::Vector2f SpriteGO::GetSize() const
{
	sf::FloatRect rect = sprite.getLocalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void SpriteGO::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	sprite.setScale(scale);
}

void SpriteGO::Init()
{
}

void SpriteGO::Release()
{
}

void SpriteGO::Reset()
{
	GameObject::Reset();
	sf::Texture* tex = Resources.GetTexture(textureID);
	if (tex != nullptr)
	{
		SetTexture(*tex);
		SetOrigin(origin);
	}
}

void SpriteGO::Update(float dt)
{
	GameObject::Update(dt);
}

void SpriteGO::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

const bool& SpriteGO::GetFlipX()
{
	return flipX;
}

void SpriteGO::SetFlipX(bool flip)
{
	scale = sprite.getScale();
	scale.x = abs(scale.x) * (flip ? -1.0f : 1.0f) * spriteDirection.x;
	sprite.setScale(scale);
	flipX = !flipX;
}

void SpriteGO::SetFlipY(bool flip)
{
	scale = sprite.getScale();
	scale.y *= abs(scale.y) * (flip ? -1.0f : 1.0f) * spriteDirection.y;
	sprite.setScale(scale);
}