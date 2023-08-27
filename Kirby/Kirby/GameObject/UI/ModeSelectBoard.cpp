#include "stdafx.h"
#include "ModeSelectBoard.h"
#include "InputManager.h"
#include "ModeButton.h"
#include "SceneManager.h"
#include "RectangleShapeGO.h"

void ModeSelectBoard::Reset()
{
	SpriteGO::Reset();
	outLine->SetFillColor(sf::Color::Transparent);
	outLine->SetOutlineThickness(2.0f);
	outLine->SetOutlineColor(sf::Color::Red);
	currentModeIndex = 0;
	RefreshOutLine();
}

void ModeSelectBoard::RefreshOutLine()
{
	for (int i = 0; i < modes.size(); i++)
	{
		if (i == currentModeIndex)
		{
			modes[i]->sortLayer = 5;
		}
		else
		{
			modes[i]->sortLayer = 1;
		}
	}
	ModeButton* mode = modes[currentModeIndex];
	outLine->SetSize({ mode->sprite.getGlobalBounds().width, mode->sprite.getGlobalBounds().height });
	outLine->SetPosition(mode->GetPosition());
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
		outLine->SetOutlineColor(sf::Color::Red);
	}
	else
	{
		outLine->SetOutlineColor(sf::Color::Transparent);
	}

	if (Input.GetKeyDown(sf::Keyboard::Right))
	{
		for (int i = currentModeIndex; i < modes.size(); i++)
		{
			if (i < modes.size() - 1 && !modes[i + 1]->IsLock())
			{
				currentModeIndex = i + 1;
				break;
			}
		}
		RefreshOutLine();
	}

	if (Input.GetKeyDown(sf::Keyboard::Left))
	{
		for (int i = currentModeIndex; i > 0; i--)
		{
			if (i > 0 && !modes[i - 1]->IsLock())
			{
				currentModeIndex = i - 1;
				break;
			}
		}
		RefreshOutLine();
	}

	if (Input.GetKeyDown(sf::Keyboard::X))
	{
		if (!modes[currentModeIndex]->HasGuide() || modes[currentModeIndex]->IsShowGuide())
		{
			if (modes[currentModeIndex]->GetNextSceneID() == SceneId::None)
			{
				return;
			}
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
	//window.draw(outLine);
}
