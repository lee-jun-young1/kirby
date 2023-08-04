#include "stdafx.h"
#include "UIButton.h"
#include "InputManager.h"
#include "SceneManager.h"

UIButton::UIButton(const std::string textureID, const std::string& name)
	:SpriteGO(textureID, name)
{
}

UIButton::~UIButton()
{
}

void UIButton::Init()
{
	SpriteGO::Init();
}

void UIButton::Release()
{
	SpriteGO::Release();
}

void UIButton::Reset()
{
	SpriteGO::Reset();

	isHover = false;
}

void UIButton::Update(float dt)
{
	SpriteGO::Update(dt);
	sf::Vector2f mousePos = Input.GetMousePosition();
	sf::Vector2f uiMousePos = SCENE_MANAGER.GetCurrentScene()->ScreenToUIPosition(mousePos);

	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

	if (!prevHover && isHover)
	{
		//Enter
		if (OnEnter != nullptr)
		{
			OnEnter();
		}
	}
	if (prevHover && !isHover)
	{
		//Exit
		if (OnExit != nullptr)
		{
			OnExit();
		}
	}

	if (isHover && Input.GetMouseButtonUp(sf::Mouse::Left))
	{
		if (OnClick != nullptr)
		{
			OnClick();
		}
	}
}

void UIButton::Draw(sf::RenderWindow& window)
{
	SpriteGO::Draw(window);
}
