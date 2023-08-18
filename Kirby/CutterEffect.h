#pragma once
#include "SpriteGO.h"
class CutterEffect : public SpriteGO
{
public:
	virtual void OnTriggerEnter(Collider* col) override;
};

