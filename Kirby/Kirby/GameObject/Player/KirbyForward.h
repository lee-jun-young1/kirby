#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
class Kirby;

class KirbyForward : public GameObject
{
protected:
	BoxCollider* collider;
	Kirby* kirby;
public:
	KirbyForward(const std::string& name = "") : GameObject(name) {
		collider = (BoxCollider*)AddComponent(new BoxCollider(*this));
		collider->SetTrigger(true);
		collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		SetOffset({ -12.0f, -24.0f });
	}
	void SetOffset(const sf::Vector2f& offset) { collider->SetOffset(offset); }
	void SetKirby(Kirby* kirby) { this->kirby = kirby; }
	virtual void Update(float dt) override;
	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
};

