#pragma once
#include "Mob.h"
class Bear : public Mob
{
public:
    Bear(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Mob_Bear.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
};

