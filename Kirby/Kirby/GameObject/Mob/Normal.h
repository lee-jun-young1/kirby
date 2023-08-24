#pragma once
#include "Mob.h"
class Normal : public Mob
{
public:
    Normal(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/mob_normal.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
};

