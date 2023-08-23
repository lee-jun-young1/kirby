#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "Mob.h"
#include "Cutter.h"
#include "SemiBossBomb.h"
class MobPool : public GameObject
{
protected:
	ObjectPool<Mob> mobs;
	ObjectPool<SemiBossBomb> semiBossBombs;
	ObjectPool<Cutter> cutters;

public:
	MobPool(const std::string& name = "") : GameObject(name) {}

	Cutter* GetCutter();
	void ClearAllPool();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

