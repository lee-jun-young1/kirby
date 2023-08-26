#pragma once
#include "Scene.h"
class SceneExample : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;
	float testRotation = 0.0f;

	int count = 0;

	sf::View backgroundView;
	int backgroundLayer = -10;
public:
	SceneExample();
	virtual ~SceneExample() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void LoadData(const std::wstring& path);
};

