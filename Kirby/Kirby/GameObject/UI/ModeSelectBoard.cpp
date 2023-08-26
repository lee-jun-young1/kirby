#include "stdafx.h"
#include "ModeSelectBoard.h"
#include "InputManager.h"
#include "ModeButton.h"
#include "SceneManager.h"

void ModeSelectBoard::Reset()
{
	SpriteGO::Reset();
	outLine.setOutlineThickness(2.0f);
	outLine.setOutlineColor(sf::Color::Red);
	currentModeIndex = 0;
	RefreshOutLine();
}

void ModeSelectBoard::RefreshOutLine()
{
	ModeButton* mode = modes[currentModeIndex];
	outLine.setSize({ mode->sprite.getGlobalBounds().width, mode->sprite.getGlobalBounds().height });
	outLine.setPosition(mode->GetPosition());
}

void ModeSelectBoard::Update(float deltaTime)
{
	twinkleTimer += deltaTime;

	if (twinkleTimer >= twinkleInterval)
	{
		isTwinkle = !isTwinkle;
		twinkleTimer = 0.0f;
	}

	if (isTwinkle)
	{
		outLine.setOutlineColor(sf::Color::Red);
	}
	else
	{
		outLine.setOutlineColor(sf::Color::Transparent);
	}

	if (Input.GetKeyDown(sf::Keyboard::Left))
	{
		if (currentModeIndex == modes.size() - 1)
		{
			return;
		}
		++currentModeIndex;
		RefreshOutLine();
	}

	if (Input.GetKeyDown(sf::Keyboard::Right))
	{
		if (currentModeIndex == 0)
		{
			return;
		}
		--currentModeIndex;
		RefreshOutLine();
	}

	if (Input.GetKeyDown(sf::Keyboard::X))
	{
		if (modes[currentModeIndex]->IsShowGuide())
		{
			SCENE_MANAGER.ChangeScene(modes[currentModeIndex]->GetNextSceneID());
		}
		else
		{
			modes[currentModeIndex]->ShowGuide();
		}
	}
	if (Input.GetKeyDown(sf::Keyboard::C))
	{
		if (modes[currentModeIndex]->IsShowGuide())
		{
			modes[currentModeIndex]->CloseGuide();
		}
	}
}

void ModeSelectBoard::Draw(sf::RenderWindow& window)
{
	SpriteGO::Draw(window);
	window.draw(outLine);
}
