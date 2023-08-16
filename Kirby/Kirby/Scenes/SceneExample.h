#pragma once
#include "Scene.h"

class CameraPointer;
class SceneExample : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;
	float testRotation = 0.0f;
	
	CameraType cameraType = CameraType::Fixed;
	CameraType prevCameraType = CameraType::None;
	float cameraTime = 0.0f;
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

	const CameraType& GetCameraType() const { return cameraType; }
	const CameraType& GetPrevCameraType() const { return prevCameraType; }
	void SetCameraType(const CameraType& type) { this->cameraType = type; }
	void SetPrevCameraType(const CameraType& type) { this->prevCameraType = type; }
};

