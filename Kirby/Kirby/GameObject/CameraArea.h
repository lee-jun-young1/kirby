#pragma once
#include "RectangleShapeGO.h"

class Camera;
class Collider;
class CameraArea : public RectangleShapeGO
{
protected:
	CameraType type = CameraType::None;
	Camera* camera = nullptr;
	
	bool isOn = false;
public:
	CameraArea(const string& name = "") : RectangleShapeGO(name) { }

	const CameraType& GetType() const { return type; }
	const Camera* GetCamera() const { return camera; }
	void SetType(CameraType type) { this->type = type; }
	void SetCamera(Camera* camera) { this->camera = camera; }

	virtual void Reset() override;
	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
};

