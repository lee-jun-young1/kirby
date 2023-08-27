#pragma once
#include "Mob.h"
class Bear : public Mob
{
    bool isRun = false;
public:
    Bear(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Mob_Bear.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
    void UpdateMove(float dt);
    virtual void Reset() override;
};

