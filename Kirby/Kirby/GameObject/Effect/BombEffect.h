#pragma once
#include "SpriteGO.h"
#include <Animator.h>
#include <BoxCollider.h>
class EffectPool;

class BombEffect : public SpriteGO
{
protected:
    EffectPool* pool;
    float bombTime = 0.0f;
    Animator* animator;
    float time = 0.0f;
    BoxCollider* collider;
public:
    BombEffect(const std::string textureID = "sprites/effects/Boom.png", const std::string& name = "BombEffect")
        :SpriteGO(textureID, name) {};
    virtual void Update(float deltaTime) override;
    virtual void OnTriggerEnter(Collider* col) override;
    virtual void OnTriggerStay(Collider* col) override;
    void SetCollider(BoxCollider* collider) { this->collider = collider; }
    void SetPool(EffectPool* pool) { this->pool = pool; }
    void SetAnimator(Animator* animator) { this->animator = animator; }
    void Fire(float bombTime);
};

