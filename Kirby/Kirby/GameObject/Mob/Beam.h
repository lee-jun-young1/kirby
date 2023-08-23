#pragma once
#include "Mob.h"
class Beam : public Mob
{

public:
    Beam(KirbyAbility type = KirbyAbility::Beam, const std::string textureID = "sprites/mob/Mob_Beam.png", const string& name = "Beam")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
};

