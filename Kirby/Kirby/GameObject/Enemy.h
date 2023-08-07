#pragma once
#include "SpriteGO.h"
class Enemy : public SpriteGO
{
protected:
	EnemyType enemyType;
public:
	const EnemyType& GetEnemyType() const { return enemyType; }
};

