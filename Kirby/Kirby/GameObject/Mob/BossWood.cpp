#include "stdafx.h"
#include "BossWood.h"
#include <Playable.h>
#include <StatusUI.h>
#include <SceneManager.h>
#include <Utils.h>

void BossWood::Damage(const int& damage, const float hitAxisX)
{
    state = State::Hit;
    animator->SetEvent(damage > 10 ? "HeavyHit" : "LightHit");
    currentHitTime = 0.0f;

    StatusUI* ui = (StatusUI*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("StatusUI");
    currentHP -= damage;
    ui->SetEnemyHP(currentHP / (float)maxHP);
    if (currentHP <= 0.0f)
    {
        animator->SetEvent("Death");
        pattern = Pattern::Death;
    }
}

void BossWood::Reset()
{
	SpriteGO::Reset();
    eventTime = 0.0f;
}

void BossWood::Update(float dt)
{
    eventTime += dt;
    if (eventTime > 1.0f)
    {
        switch (pattern)
        {
        case Pattern::None:
        {
            pattern = (Pattern)Utils::RandomRange(0, 3);
        }
        break;
        case Pattern::Apple:
        {
            eventTime -= 1.0f;
            WoodEffect* apple = effectPool->GetWoodEffect(PhysicsLayer::EnemyEffect);
            apple->SetType(WoodEffect::EffectType::Apple);
            apple->sortLayer = 5;
            apple->AddTag("Suctionable");
            apple->SetPosition(GetPosition() - GetOrigin() + sf::Vector2f(-48.0f, -20.0f) + sf::Vector2f(Utils::RandomValue() * -144.0f, -20.0f));
            eventCount++;
            if (eventCount > 3)
            {
                eventCount = 0;
                eventTime -= 1.5f;
                pattern = Pattern::None;
            }
        }
        break;
        case Pattern::Breath:
        {
            eventTime -= 0.5f;
            WoodEffect* breath = effectPool->GetWoodEffect(PhysicsLayer::EnemyEffect);
            breath->SetType(WoodEffect::EffectType::Breath);
            breath->sortLayer = 5;
            breath->SetPosition(GetPosition() - GetOrigin() + sf::Vector2f(-24.0f, 45.0f));
            breath->Fire();
            eventCount++;
            if (eventCount > 3)
            {
                eventCount = 0;
                eventTime -= 1.5f;
                pattern = Pattern::None;
            }
        }
            break;
        }
         
    }
}

void BossWood::OnTriggerEnter(Collider* col)
{
    if (col->GetGameObject().GetName() == "Ground" && animator->GetClipName() == "Jump")
    {
        animator->SetEvent("Idle");
    }
    if (col->GetGameObject().GetName() == "Kirby")
    {
        ((Playable*)&col->GetGameObject())->Damage(atk, -1.0f);
        RigidBody2D* rig = (RigidBody2D*)col->GetGameObject().GetComponent(ComponentType::RigidBody);
    }
}

void BossWood::OnTriggerStay(Collider* col)
{
}