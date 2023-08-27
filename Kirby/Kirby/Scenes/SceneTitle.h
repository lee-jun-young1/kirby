#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
public:
	enum class TitleStatus
	{
		None = -1,
		DataSlot
	};
protected:
	TitleStatus status = TitleStatus::None;

public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};
