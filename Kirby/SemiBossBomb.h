#pragma once
#include "Mob.h"
#include "EffectPool.h"
class SemiBossBomb : public Mob
{
    sf::Vector2f jumpPower[3] = { {10.0f, -200.0f}, {75.0f, -200.0f}, {150.0f, -200.0f} };
    sf::Vector2f throwPower[3] = { {20.0f, -100.0f}, {75.0f, -100.0f}, {150.0f, -100.0f} };
    int jumpCount = 0;
    int throwCount = 0;
    EffectPool* effectPool;
public:
    SemiBossBomb(KirbyAbility type, const std::string textureID = "", const string& name = "") : Mob(type, textureID, name) {};
    virtual void Reset() override;
    virtual void Damage(const int& damage, const float hitAxisX) override;

    virtual void UpdateIdle(float dt);
    virtual void UpdateMove(float dt);
    virtual void UpdateThrow(float dt);
    virtual void UpdateTripleThrow(float dt);
    virtual void UpdateHit(float dt);
    virtual void UpdateSuction(float dt);

    virtual void OnCollisionEnter(Collider* col) override;
    virtual void OnCollisionStay(Collider* col) override;

    void SetEffectPool(EffectPool* effectPool) { this->effectPool = effectPool; }
};

