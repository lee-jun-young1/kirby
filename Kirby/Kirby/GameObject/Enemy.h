#pragma once
#include "SpriteGO.h"
class Enemy : public SpriteGO
{
protected:
	EnemyType enemyType;
public:
	Enemy(const std::string textureID = "", const std::string& name = "");

	const EnemyType& GetEnemyType() const { return enemyType; }
	void SetEnemyType(const EnemyType& type) { enemyType = type; }
};

