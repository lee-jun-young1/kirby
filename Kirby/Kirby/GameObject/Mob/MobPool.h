#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "Mob.h"
#include "Cutter.h"

class MobPool : public GameObject
{
protected:
	ObjectPool<Mob> mobs;

public:
	MobPool(const std::string& name = "") : GameObject(name) {}

	Mob* GetMob(const EnemyType& type);
	void ClearPool();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

