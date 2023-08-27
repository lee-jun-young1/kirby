#include "stdafx.h"
#include "ModeButton.h"
#include "InputManager.h"

bool ModeButton::HasGuide()
{
	return guide != nullptr;
}

void ModeButton::ShowGuide()
{
	if (guide == nullptr)
	{
		return;
	}
	guide->SetActive(true);
	showGuide = true;
}

void ModeButton::CloseGuide()
{
	if (guide == nullptr)
	{
		return;
	}
	guide->SetActive(false);
	showGuide = false;
}

void ModeButton::Reset()
{
	SpriteGO::Reset();
	if (guide != nullptr)
	{
		guide->sortLayer = 100;
		guide->SetActive(false);
		showGuide = false;
	}
	//shape->setOutlineThickness(10.0f);
	//shape->setOutlineColor(sf::Color::Red);
}

void ModeButton::Update(float deltaTime)
{

}

