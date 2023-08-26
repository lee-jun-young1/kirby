#include "stdafx.h"
#include "Background.h"
#include "InputManager.h"
#include "Animation.h"
void Background::Init()
{
	sortLayer = -99;
}

void Background::Reset()
{
	SpriteGO::Reset();
	SetOrigin(Origins::TL);
}

void Background::Draw(sf::RenderWindow& window)
{
	SpriteGO::Draw(window);
}
