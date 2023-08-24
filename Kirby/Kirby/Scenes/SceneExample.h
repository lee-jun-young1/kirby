#pragma once
#include "Scene.h"
#include "json.h"

class Camera;
class VertexArrayGO;
class SceneExample : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;
	float testRotation = 0.0f;

	Camera* currentCamera = nullptr;
	Camera* previousCamera = nullptr;
	float cameraTime = 0.0f;
	int count = 0;

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
	void LoadDataEnter(const std::wstring& path);

	const Camera* GetCamera() const { return currentCamera; }
	void SetCamera(Camera* camera = nullptr);

	//Temp Background
	VertexArrayGO* CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize = { 0.f, 0.f }, const std::string& textureId = "");
};

