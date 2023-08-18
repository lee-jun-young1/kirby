#pragma once
#include "SpriteGO.h"
#include <Animator.h>

class BombEffect : public SpriteGO
{
protected:
    float bombTime;
    Animator* animator;
public:
    virtual void Update(float deltaTime) override;
    virtual void OnCollisionEnter(Collider* col) override;
};

