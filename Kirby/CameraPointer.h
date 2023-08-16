#pragma once
#include "RectangleShapeGO.h"
class Kirby;
class CameraPointer : public RectangleShapeGO
{
protected:
	CameraType type = CameraType::None;
	sf::Vector2f activePosition;
	bool isOneOff = false;

public:
	CameraPointer(const string& name = "") : RectangleShapeGO(name) {}
	virtual ~CameraPointer() {};

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	const CameraType& GetType() const { return type; }
	void SetType(const CameraType& type) { this->type = type; }

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
};

