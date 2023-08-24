#pragma once
#include "Mob.h"
class Fly : public Mob
{
public:
    Fly(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Mob_Fly.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
};

