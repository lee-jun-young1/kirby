#include "stdafx.h"
#include "SpringBreezeKirby.h"
#include "Animation.h"
#include "InputManager.h"
void SpringBreezeKirby::Reset()
{
	Animation* ani = (Animation*)AddComponent(new Animation(*this));
	ani->SetClip(Resources.GetAnimationClip("animations/UI/SpringBreezeKirby.csv"));
	ani->Play();

	GameObject* go = targets[currentTargetIndex];
	SetPosition({ go->GetPosition().x - sprite.getGlobalBounds().width - 8.0f, go->GetPosition().y - 8.0f });
}

void SpringBreezeKirby::Update(float deltaTime)
{
	if (Input.GetKeyDown(sf::Keyboard::Down))
	{
		if (currentTargetIndex == targets.size() - 1)
		{
			return;
		}
		GameObject* go = targets[currentTargetIndex++];
		SetPosition({ go->GetPosition().x - sprite.getGlobalBounds().width - 8.0f, go->GetPosition().y - 8.0f });
	}

	if (Input.GetKeyDown(sf::Keyboard::Up))
	{
		if (currentTargetIndex == 0)
		{
			return;
		}
		GameObject* go = targets[currentTargetIndex--];
		SetPosition({ go->GetPosition().x - sprite.getGlobalBounds().width - 8.0f, go->GetPosition().y - 8.0f });
	}
}
