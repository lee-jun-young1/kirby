#pragma once
#include "RectangleShapeGO.h"
#include "json.h"
class SpriteGO;
class Camera : public RectangleShapeGO
{
protected:
	CameraType type = CameraType::None;
	CameraType prevType = CameraType::None;

	sf::View* view = nullptr;
	sf::Vector2f viewArea;
	sf::Vector2f size;
	sf::Vector2f cellSize = { 24.0f, 24.0f };
	
	SpriteGO* target = nullptr;
	sf::Vector2f cameraCenter;
	float cameraTime = 0.0f;

	bool toggle = false;

	bool isIn = false;
	bool isStay = false;
	bool isOut = false;

	Json::Value data;
public:
	Camera(const string& name = "") : RectangleShapeGO(name) {}
	virtual ~Camera() {};

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetTarget(SpriteGO* go) { this->target = go; }
	void SetData(const Json::Value& data) { this->data = data; };
	void SetView(sf::View* view) { this->view = view; }

	const CameraType& GetType() const { return type; }
	void SetType(const CameraType& type) { this->type = type; }

	void MoveCamera(float dt);

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;

	void Deactivate() {}
	void Activate() {}
};

