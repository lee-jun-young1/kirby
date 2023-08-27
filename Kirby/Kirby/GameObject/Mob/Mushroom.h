#pragma once
#include "Mob.h"
class Mushroom : public Mob
{
    bool hasHead = true;
    SpriteGO* head;
public:
    Mushroom(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Mob_mushroom.png", const string& name = "Mob")
        :Mob(type, textureID, name) {}

    virtual void Init() override;
    void UpdateIdle(float dt);
    void Reset();
    void OnCollisionEnter(Collider* col);
};

