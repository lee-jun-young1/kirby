#include "stdafx.h"
#include "BeamEffect.h"
#include "Utils.h"
#include "EffectPool.h"
#include <Mob.h>

void BeamEffect::Update(float deltaTime)
{
    time += deltaTime;
    if (time > 1.0f)
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
}

const float& BeamEffect::GetTotalRotation() const
{
    if (prevNode != nullptr)
    {
        return prevNode->GetTotalRotation() + effectRotation;
    }
    return effectRotation;
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
