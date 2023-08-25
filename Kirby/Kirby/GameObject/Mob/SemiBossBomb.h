#pragma once
#include "Mob.h"
#include "EffectPool.h"
class SemiBossBomb : public Mob
{
    enum class State
    {
        None,
        Jump,
        TripleJump,
        Dash,
        Throw,
        TripleThrow,
        Death,
        Suction,
        Count,
    };
    sf::Vector2f jumpPower[3] = { {10.0f, -200.0f}, {75.0f, -200.0f}, {150.0f, -200.0f} };
    sf::Vector2f throwPower[3] = { {20.0f, -100.0f}, {75.0f, -100.0f}, {150.0f, -100.0f} };
    int jumpCount = 0;
    int throwCount = 0;
    EffectPool* effectPool;

    function<void(Collider*)> onCollisionEnter;
public:
    SemiBossBomb(KirbyAbility type = KirbyAbility::Bomb, const std::string textureID = "sprites/mob/SB_Bomb.png", const string& name = "Mob") : Mob(type, textureID, name) {};
    virtual void Init() override;
    virtual void OnDisable() override;
    virtual void Reset() override;
    void WakeUp();
    virtual void Damage(const int& damage, const float hitAxisX) override;

    void SetState(State state);
    virtual void Update(float dt) override;

    virtual void OnCollisionEnter(Collider* col) override;
    void JumpCollisionEnter(Collider* col);
    void TripleJumpCollisionEnter(Collider* col);
    void ThrowCollisionEnter(Collider* col);
    void TripleThrowCollisionEnter(Collider* col);
    void DeathCollisionEnter(Collider* col);
    virtual void OnCollisionStay(Collider* col) override;

    void SetEffectPool(EffectPool* effectPool) { this->effectPool = effectPool; }
};

