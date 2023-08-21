#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "Mob.h"

class Kirby;

class Suction : public GameObject
{
private:
	BoxCollider* collider;
	Kirby* kirby;
	list<Mob*> suctionList;
public:
	Suction(const string& name = "Suction") : GameObject(name) {};
	void SetKirby(Kirby* kirby) { this->kirby = kirby; }
	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void OnEnable() override;
	virtual void OnDisable() override;

	virtual void OnTriggerStay(Collider* col) override;
};

