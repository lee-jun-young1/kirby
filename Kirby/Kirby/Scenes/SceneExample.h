#pragma once
#include "Scene.h"

class Camera;
class SceneExample : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;
	float testRotation = 0.0f;

	Camera* currentCamera = nullptr;
	Camera* previousCamera = nullptr;
	float cameraTime = 0.0f;
	std::vector<Camera*> cameras;

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

	const Camera* GetCamera() const { return currentCamera; }
	void SetCamera(Camera* camera = nullptr);
};

