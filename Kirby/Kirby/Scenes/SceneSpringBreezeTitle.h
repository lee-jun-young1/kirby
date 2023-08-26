#pragma once
#include "Scene.h"
class SceneSpringBreezeTitle : public Scene
{
protected:

public:
	SceneSpringBreezeTitle();
	virtual ~SceneSpringBreezeTitle() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

