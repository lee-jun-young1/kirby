#pragma once
#include "RectangleShapeGO.h"
class ModeButton : public RectangleShapeGO
{
protected:
	bool isFocus = false;

	bool isTwinkle = false;
	float twinkleTimer = 0.0f;
	float twinkleInterval = 0.5f;
public:
	ModeButton(const string& name = "") : RectangleShapeGO(name){}

	void SetFocus(bool focus) { this->isFocus = focus; }

	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	

};

