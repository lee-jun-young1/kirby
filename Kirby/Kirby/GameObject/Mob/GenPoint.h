#pragma once
#include "GameObject.h"
class Mob;
class MobPool;
class GenPoint : public GameObject
{
protected:
	EnemyType type = EnemyType::None;
	MobPool* pool = nullptr;
	Mob* mob = nullptr;
public:
	GenPoint(const std::string& name) : GameObject(name) {}

	virtual void Reset() override;

	void SetEnemyType(EnemyType type) { this->type = type; }
	const EnemyType& GetType() const { return type; }

	void SetMobPool(MobPool* pool) { this->pool = pool; }
	void MobRemove();
};

