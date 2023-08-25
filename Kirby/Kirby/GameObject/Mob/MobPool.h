#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "Mob.h"
#include "Cutter.h"
#include "SemiBossBomb.h"
#include "Bomb.h"
#include "Beam.h"
#include "Normal.h"
#include "Fly.h"
#include "Bear.h"
#include "Chick.h"
#include "Mushroom.h"
#include "BossWood.h"

class MobPool : public GameObject
{
protected:
	ObjectPool<Cutter> cutters;
	ObjectPool<Bomb> bombs;
	ObjectPool<Beam> beams;
	ObjectPool<Normal> normals;
	ObjectPool<Fly> flies;
	ObjectPool<Bear> bears;
	ObjectPool<Mushroom> mushrooms;
	ObjectPool<Chick> chicks;
	ObjectPool<SemiBossBomb> semiBossBombs;
	ObjectPool<BossWood> bossWoods;

public:
	MobPool(const std::string& name = "") : GameObject(name) {}

	Mob* GetMob(EnemyType type);
	Cutter* GetCutter();
	Bomb* GetBomb();
	Beam* GetBeam();
	Normal* GetNormal();
	Fly* GetFly();
	Bear* GetBear();
	Chick* GetChick();
	Mushroom* GetMushroom();
	SemiBossBomb* GetSemiBossBomb();
	BossWood* GetBossWood();


	void MobReturn(Mob* mob);
	void ClearAllPool();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

