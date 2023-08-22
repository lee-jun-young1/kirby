#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "Ground.h"
#include "ThrowableGround.h"

class GroundPool : public GameObject
{
protected:
	ObjectPool<Ground> grounds;
	ObjectPool<ThroughtableGround> ThroughGrounds;

public:
	GroundPool(const std::string& name = "") : GameObject(name) {}

	Ground* GetGround(const GroundType& type);
	Ground* GetThroughGround();

	void ReturnGround(Ground* ground);
	void ReturnThroughGround(ThroughtableGround* ground);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

