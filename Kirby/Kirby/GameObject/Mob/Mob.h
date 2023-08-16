#pragma once
#include "SpriteGO.h"
#include <Animator.h>
#include <RigidBody2D.h>
class Mob : public SpriteGO
{
protected:
    enum class State 
    {
        Idle,
        Move,
        Hit,
        Suction,
    };
    bool suctionable = true;
    KirbyAbility type;
    float speed = -15.0f;
    State state = State::Move;

    float eventTime = 4.0f;
    float currentEventTime = 2.0f;

    function<void(float)> update;

    Animator* animator;
    RigidBody2D* rigidbody;

    GameObject* target;
    float suctionTime = 0.0f;
    sf::Vector2f suctionStartPos;

    float hitTime = 1.0f;
    float currentHitTime = 0.0f;
public:
    Mob(KirbyAbility type, const std::string textureID = "", const string& name = "") : SpriteGO(textureID, name), type(type) {};
    bool IsSuctionable() { return suctionable; }
    KirbyAbility GetType() { return type; }

    void SetAnimator(Animator* animator) { this->animator = animator; };
    void SetRigidBody(RigidBody2D* rigidbody) { this->rigidbody = rigidbody; };

    virtual void Reset() override;

    virtual void Update(float dt) override;
    void UpdateIdle(float dt);
    void UpdateMove(float dt);
    void UpdateHit(float dt);
    void UpdateSuction(float dt);

    void SetSuction(GameObject* target);

    void Damage(const int& damage);

    virtual void OnCollisionEnter(Collider* col) override;
};

