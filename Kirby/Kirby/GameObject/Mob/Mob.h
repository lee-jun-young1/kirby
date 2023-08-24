#pragma once
#include "SpriteGO.h"
#include <Animator.h>
#include <RigidBody2D.h>
class MobPool;
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
    EnemyType enemyType;
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

    float hitTime = 0.5f;
    float currentHitTime = 0.0f;

    float atk = 1.0f;

    sf::Vector2f regenPosition;

    int maxHP = 10;
    int currentHP = 10;

    MobPool* mobPool = nullptr;
public:
    Mob(KirbyAbility type, const std::string textureID = "", const string& name = "") : SpriteGO(textureID, name), type(type) {};
    bool IsSuctionable() { return suctionable; }
    KirbyAbility GetType() { return type; }
    EnemyType GetEnemyType() { return enemyType; }
    const sf::Vector2f& GetRegenPosition() const { return regenPosition; };

    void SetEnemeyType(EnemyType type) { this->enemyType = type; }
    void SetAnimator(Animator* animator) { this->animator = animator; };
    void SetRigidBody(RigidBody2D* rigidbody) { this->rigidbody = rigidbody; };
    void SetRegenPosition(const sf::Vector2f regenPosition) { this->regenPosition = regenPosition; }
    void SetMobPool(MobPool* mobPool) { this->mobPool = mobPool; }

    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void UpdateIdle(float dt);
    virtual void UpdateMove(float dt);
    virtual void UpdateHit(float dt);
    virtual void UpdateSuction(float dt);

    void SetSuction(GameObject* target);
    
    virtual void Damage(const int& damage, const float hitAxisX);

    virtual void OnCollisionEnter(Collider* col) override;
    virtual void OnCollisionStay(Collider* col) override;
};

