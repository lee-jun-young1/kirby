#pragma once
#include "Mob.h"
class Mushroom : public Mob
{
public:
    Mushroom(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Mob_mushroom.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
};

