#include "stdafx.h"
#include "WoodEffect.h"
#include "Utils.h"
#include <Kirby.h>

void WoodEffect::OnTriggerEnter(Collider* col)
{
    if (col->GetGameObject().HasTag("Kirby"))
    {
        ((Kirby*)&col->GetGameObject())->Damage(1.0f, col->GetGameObject().GetPosition().x < GetPosition().x + sprite.getGlobalBounds().width * 0.5f ? -1.0f : 1.0f);
    }
    if (onTriggerEnter != nullptr)
    {
        onTriggerEnter(col);
    }
}

void WoodEffect::AppleTriggerEnter(Collider* col)
{

    if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y > 0.0f)
    {
        if (isBounced)
        {
            pool->ReturnWoodEffect(this);
            return;
        }
        if (Utils::RandomRange(0, 2) == 0)
        {
            rigidbody->SetVelocity({ -100.0f, -150.0f });
        }
        else
        {
            rigidbody->SetVelocity({ 100.0f, -150.0f });
        }
        isBounced = true;
    }
}

void WoodEffect::SetType(EffectType type)
{
    switch (type)
    {
    case EffectType::Apple:
        animator->SetState("Apple");
        rigidbody->SetVelocity({ 0.0f, 0.0f });
        rigidbody->SetGravity(true);
        onTriggerEnter = std::bind(&WoodEffect::AppleTriggerEnter, this, std::placeholders::_1);
        isBounced = false;
        break;
    case EffectType::Breath:
        animator->SetState("Breath");
        rigidbody->SetVelocity({ 0.0f, 0.0f });
        rigidbody->SetGravity(false);
        onTriggerEnter = nullptr;
        break;
    }
}

void WoodEffect::Reset()
{
    SpriteGO::Reset();
    isBounced = false;
    lifeTime = 5.0f;
}

void WoodEffect::Update(float dt)
{
    SpriteGO::Update(dt);
    lifeTime -= dt;
    if (lifeTime <= 0.0f)
    {
        pool->ReturnWoodEffect(this);
    }
}

void WoodEffect::Fire()
{
    rigidbody->SetVelocity({ -100.0f, 0.0f });
}
