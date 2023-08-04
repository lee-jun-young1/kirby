#pragma once
#include "SpriteGO.h"
class UIButton : public SpriteGO
{
protected:
	bool isHover = false;
public:
	UIButton(const std::string textureID = "", const std::string& name = "");
	virtual ~UIButton() override;
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	sf::Text text;

	std::function<void()> OnClick;
	std::function<void()> OnEnter;
	std::function<void()> OnExit;
};

