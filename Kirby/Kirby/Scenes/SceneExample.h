#pragma once
#include "Scene.h"

class VertexArrayGO;
class SceneExample : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;

	float testRotation = 0.0f;

	CameraType cameraType = CameraType::Free;
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

	VertexArrayGO* CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize = { 0.f, 0.f }, const std::string& textureId = "");
};

