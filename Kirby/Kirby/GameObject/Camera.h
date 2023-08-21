#pragma once
#include "RectangleShapeGO.h"
class Kirby;
class Camera : public RectangleShapeGO
{
protected:
	CameraType type = CameraType::None;
	CameraType prevType = CameraType::None;
	bool isOneOff = false;

	GameObject* targetGO = nullptr;
	sf::View* targetView = nullptr;
	sf::Vector2f viewArea;
public:
	Camera(const string& name = "") : RectangleShapeGO(name) {}
	virtual ~Camera() {};

	virtual void Init() override;
	virtual void Reset() override;
	//virtual void Update(float dt) override;

	void SetTarget(GameObject* go) { this->targetGO = go; }
	void SetTargetView(sf::View* view) { this->targetView = view; }

	const CameraType& GetType() const { return type; }
	void SetType(const CameraType& type) { this->type = type; }

	const sf::Vector2f& CalculateCameraPosition(const sf::Vector2f& rate = {1.0f, 1.0f});

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
};

