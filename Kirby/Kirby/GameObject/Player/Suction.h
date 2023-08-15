#pragma once
#include "GameObject.h"
#include "BoxCollider.h"

class Kirby;

class Suction : public GameObject
{
private:
	BoxCollider* collider;
	Kirby* kirby;
public:
	Suction(const string& name = "Suction") : GameObject(name) {};
	void SetKirby(Kirby* kirby) { this->kirby = kirby; }
	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void OnTriggerStay(Collider* col) override;
};

