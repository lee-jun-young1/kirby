#pragma once
#include "Mob.h"
class Cutter : public Mob
{
public:
    Cutter(KirbyAbility type = KirbyAbility::Cutter, const std::string textureID = "sprites/mob/mob_Cutter.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
    virtual void Reset() override;
    virtual void UpdateIdle(float dt) override;
    virtual void UpdateHit(float dt) override;
    virtual void Damage(const int& damage, const float hitAxisX) override;
};

