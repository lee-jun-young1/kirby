#pragma once
#include "SpriteGO.h"
#include <BoxCollider.h>
class ThroughtableGround :
    public SpriteGO
{
protected:
	BoxCollider* collider;
public:
	ThroughtableGround(const std::string textureID = "sprites/temp/tempThroughtable.png", const string& name = "ThroughtableGround") :SpriteGO(textureID, name) {};
	virtual void OnCollisionEnter(Collider* col) override;
	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;

	void SetCollider(BoxCollider* collider) { this->collider = collider; }
};

