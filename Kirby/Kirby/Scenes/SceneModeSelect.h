#pragma once
#include "Scene.h"
class SceneModeSelect : public Scene
{
public:
	enum class ModeSelectStatus
	{
		None = -1,
		Guide,
	};
protected:
	ModeSelectStatus status = ModeSelectStatus::None;

public:
	SceneModeSelect();
	virtual ~SceneModeSelect() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

