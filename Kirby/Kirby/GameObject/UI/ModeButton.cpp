#include "stdafx.h"
#include "ModeButton.h"
#include "InputManager.h"

void ModeButton::ShowGuide()
{
	guide->SetActive(true);
	showGuide = true;
}

void ModeButton::CloseGuide()
{
	guide->SetActive(false);
	showGuide = false;
}

void ModeButton::Reset()
{
	SpriteGO::Reset();
	guide->sortLayer = 100;
	guide->SetActive(false);
	showGuide = false;
	//shape->setOutlineThickness(10.0f);
	//shape->setOutlineColor(sf::Color::Red);
}

void ModeButton::Update(float deltaTime)
{
	if (Input.GetKeyDown(sf::Keyboard::X))
	{
		//twinkleTimer += deltaTime;

		//if (twinkleTimer >= twinkleInterval)
		//{
		//	isTwinkle = !isTwinkle;
		//	twinkleTimer = 0.0f;
		//}

		//if (isTwinkle)
		//{
		//	shape->setOutlineColor(sf::Color::Red);
		//}
		//else
		//{
		//	shape->setOutlineColor(sf::Color::Transparent);
		//}
		guide->SetActive(true);
		showGuide = true;
	}
	if (Input.GetKeyDown(sf::Keyboard::C) && showGuide)
	{
		guide->SetActive(false);
		showGuide = false;
	}
}

