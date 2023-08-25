#pragma once
#include "RectangleShapeGO.h"
#include "json.h"

class Kirby;
class CameraArea;
class Camera : public GameObject
{
protected:
	CameraType type = CameraType::None;
	CameraType prevType = CameraType::None;

	sf::FloatRect areaBounds;
	sf::FloatRect prevAreaBounds;

	sf::FloatRect checkArea;
	sf::Vector2f correctSize = { 24.0f * 11.f, 24.0f * 6.f };

	float cameraTime = 0.0f;

	Kirby* kirby = nullptr;
	sf::View* view = nullptr;
	CameraArea* area = nullptr;
	std::list<GameObject*> gameObjects;

public:
	Camera(const string& name = "") : GameObject(name) {}

	virtual void Update(float deltaTime) override;

	void SetKirby(Kirby* go) { this->kirby = go; }
	void SetView(sf::View* view) { this->view = view; }
	void SetGameObjects(std::list<GameObject*> gameObjects) { this->gameObjects = gameObjects; }
	void SetCameraArea(CameraArea* area);

	const CameraType& GetType() const { return type; }
	void SetType(const CameraType& type, const sf::Vector2f& position = { 0.0f, 0.0f });

	void DeActiveCurrentArea();
	void DeActiveOtherAreas();
	void SetPrevCam();
	void SetActiveInCamera(GameObject* target);
};

