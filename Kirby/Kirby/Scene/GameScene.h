#pragma once
#include "Scene.h"
class VertexArrayGO;
class GameScene : public Scene
{
protected:

	//Camera
	sf::Vector2f movement;
	float cameraSpeed = 50.f;
public:
	GameScene();
	virtual ~GameScene();

	virtual void Enter() override;

	// Scene을(를) 통해 상속됨
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	VertexArrayGO* CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize = { 0.f, 0.f }, const std::string& textureId = "");
};

