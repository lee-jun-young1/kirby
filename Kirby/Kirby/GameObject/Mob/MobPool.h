#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "Mob.h"
#include "Cutter.h"
#include "SemiBossBomb.h"
#include "Bomb.h"
#include "Beam.h"
class MobPool : public GameObject
{
protected:
	ObjectPool<Mob> mobs;
	ObjectPool<SemiBossBomb> semiBossBombs;
	ObjectPool<Cutter> cutters;
	ObjectPool<Bomb> bombs;
	ObjectPool<Beam> beams;

public:
	MobPool(const std::string& name = "") : GameObject(name) {}

	Cutter* GetCutter();
	Bomb* GetBomb();
	Beam* GetBeam();
	
	void MobReturn(Mob* mob);
	void ClearAllPool();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

