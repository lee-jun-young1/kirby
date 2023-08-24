#pragma once
#include "RectangleShapeGO.h"
#include "json.h"

class SpriteGO;
class Kirby;
class Camera : public RectangleShapeGO
{
protected:
	CameraType type = CameraType::None;

	sf::View* view = nullptr;
	sf::Vector2f correctSize = { 216.0f, 144.0f };
	sf::Vector2f size;
	sf::FloatRect realCheckArea;
	sf::Vector2f cellSize = { 24.0f, 24.0f };

	Kirby* kirby = nullptr;
	float cameraTime = 0.0f;
public:
	Camera(const string& name = "") : RectangleShapeGO(name) {}
	virtual ~Camera() {};

	virtual void Init() override;
	virtual void Reset() override;

	void SetKirby(Kirby* go) { this->kirby = go; }
	void SetView(sf::View* view) { this->view = view; }

	const CameraType& GetType() const { return type; }
	void SetType(const CameraType& type) { this->type = type; }

	void MoveCamera(float dt);
	void SetActiveInCamera(GameObject* target);

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
};

