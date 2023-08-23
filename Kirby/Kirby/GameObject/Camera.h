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
	sf::Vector2f correctSize = { 200.0f, 150.0f };
	sf::Vector2f size;
	sf::FloatRect realCheckArea;
	sf::Vector2f cellSize = { 24.0f, 24.0f };
	
	Kirby* kirby = nullptr;
	float cameraTime = 0.0f;

	Json::Value data;
public:
	Camera(const string& name = "") : RectangleShapeGO(name) {}
	virtual ~Camera() {};

	virtual void Init() override;
	virtual void Reset() override;

	void SetKirby(Kirby* go) { this->kirby = go; }
	void SetData(const Json::Value& data) { this->data = data; };
	void SetView(sf::View* view) { this->view = view; }

	const CameraType& GetType() const { return type; }
	void SetType(const CameraType& type) { this->type = type; }

	void MoveCamera(float dt);
	void SetActiveInCamera(SpriteGO* target);

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
};

