#include "stdafx.h"
#include "BeamEffect.h"
#include "Utils.h"
#include "EffectPool.h"
#include <Mob.h>

void BeamEffect::Update(float deltaTime)
{
    time += deltaTime;
    removeTime += deltaTime;
    switch(mode)
    {
    case Mode::Whip:
        if (removeTime > 1.0f)
        {
            pool->ReturnBeamEffect(this);
        }
        if (prevNode != nullptr)
        {
            sf::Vector2f pos = effectDirection * 20.0f;
            float totalRotation = GetTotalRotation();
            pos = Utils::RotateWithPivot({ 0.0f, 0.0f }, pos, effectDirection.x * totalRotation);
            SetPosition(prevNode->GetPosition() + pos);
        }
        else
        {
            effectRotation += deltaTime * 180.0f * effectDirection.x;
        }
       break;
    case Mode::Tornado:
        if (prevNode != nullptr)
        {
            cout << time  << " , " << cos(time) << endl;
            sf::Vector2f pos = Utils::RotateWithPivot({ 0.0f, 0.0f }, { 15.0f, 0.0f }, Utils::Lerp(-effectRotation, effectRotation, abs(cos(time* 4.0f))));
            pos.x *= effectDirection.x;
            SetPosition(prevNode->GetPosition() + pos);
        }
        if (removeTime > 1.0f)
        {
            pool->ReturnBeamEffect(this);
        }
        break;
    case Mode::WindBall:
        effectRotation += 720.0f * deltaTime * effectDirection.x;
        sf::Vector2f pos = effectDirection * 5.0f;
        float totalRotation = GetTotalRotation();
        pos = Utils::RotateWithPivot({ 0.0f, 0.0f }, pos, effectDirection.x * totalRotation);
        sprite.setOrigin(effectPoint + pos);
        break;
    }
}

const float& BeamEffect::GetTotalRotation() const
{
    if (prevNode != nullptr)
    {
        return prevNode->GetTotalRotation() + effectRotation;
    }
    return effectRotation;
}

void BeamEffect::Shot(const sf::Vector2f& power)
{
    SetFlipX(power.x > 0.0f);
    effectPoint = sprite.getOrigin();
    if (power.x < 0.0f)
    {
        effectPoint.x += 72.0f;
    }
    animator->SetEvent("Fire");
    rigidbody->SetVelocity(power);
    rigidbody->SetGravity(false);
    collider->SetRect({ 0.0f, 0.0f, 30.0f, 30.0f });
    collider->SetOffset({ 21.0f, 21.0f });
    collider->SetTrigger(true);
}

void BeamEffect::SetMode(const Mode& mode)
{ 
    removeTime = 0.0f;
    this->mode = mode; 
    switch (mode)
    {
    case Mode::Whip:
    case Mode::Ball:
        animator->SetState("Beam");
        collider->SetRect({ 0.0f, 0.0f, 8.0f, 8.0f });
        collider->SetOffset({ 32.0f, 32.0f });
        collider->SetTrigger(true);
        break;
    case Mode::Tornado:
        animator->SetState("Tornado");
        collider->SetRect({ 0.0f, 0.0f, 8.0f, 8.0f });
        collider->SetOffset({ 32.0f, 32.0f });
        collider->SetTrigger(true);
        break;
    case Mode::WindBall:
        animator->SetState("Charge");
        collider->SetRect({ 0.0f, 0.0f, 8.0f, 8.0f });
        collider->SetOffset({ 32.0f, 32.0f });
        collider->SetTrigger(true);
        break;
    }
}

void BeamEffect::Return()
{
    pool->ReturnBeamEffect(this);
}

void BeamEffect::OnTriggerEnter(Collider* col)
{
    if (col->GetGameObject().HasTag("Mob"))
    {
        ((Mob*)&col->GetGameObject())->Damage(1.0f, col->GetGameObject().GetPosition().x < GetPosition().x + sprite.getGlobalBounds().width * 0.5f ? -1.0f : 1.0f);
        if (mode == Mode::Ball)
        {
            pool->ReturnBeamEffect(this);
        }
    }
    if (mode == Mode::Ball && col->GetGameObject().HasTag("Ground"))
    {
        pool->ReturnBeamEffect(this);
    }
    
}
