#pragma once
#include "Mob.h"
class Chick : public Mob
{
public:
    Chick(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Mob_chick.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
};

