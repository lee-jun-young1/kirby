#include "stdafx.h"
#include "Background.h"

void Background::Reset()
{
	SpriteGO::Reset();
	SetOrigin(Origins::TL);
	sortLayer = -99;
	repeatPosition.x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width;
}

void Background::Update(float deltaTime)
{
	
}

void Background::Draw(sf::RenderWindow& window)
{
	SpriteGO::Draw(window);

}
