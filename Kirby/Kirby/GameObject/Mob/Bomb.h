#pragma once
#include "Mob.h"
class Bomb : public Mob
{

public:
	Bomb(KirbyAbility type = KirbyAbility::Bomb, const std::string textureID = "sprites/mob/mob_Bomb.png", const string& name = "Bomb")
		:Mob(type, textureID, name) {}
	virtual void Init() override;
};

