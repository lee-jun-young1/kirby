#include "stdafx.h"
#include "ModeButton.h"

void ModeButton::Reset()
{
	RectangleShapeGO::Reset();
	shape->setOutlineThickness(2.0f);
	shape->setOutlineColor(sf::Color::Transparent);
	SetPosition({ 0.0f, 0.0f });
}

void ModeButton::Update(float deltaTime)
{
	if (isFocus)
	{
		twinkleTimer += deltaTime;

		if (twinkleTimer >= twinkleInterval)
		{
			isTwinkle = !isTwinkle;
			twinkleTimer = 0.0f;
		}

		if (isTwinkle)
		{
			shape->setOutlineColor(sf::Color::Red);
		}
		else
		{
			shape->setOutlineColor(sf::Color::Transparent);
		}
	}

}


