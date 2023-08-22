#include "stdafx.h"
#include "Mob.h"
#include <Suction.h>
#include "Utils.h"
#include <Playable.h>

void Mob::Reset()
{
    SpriteGO::Reset();
    update = std::bind(&Mob::UpdateMove, this, std::placeholders::_1);
    SetPosition(regenPosition);
}

void Mob::Update(float dt)
{
    SpriteGO::Update(dt);
    update(dt);
}

void Mob::UpdateIdle(float dt)
{
    currentEventTime += dt;
    if (currentEventTime > eventTime)
    {
        animator->SetEvent("Jump");
        currentEventTime = 0.0f;
        rigidbody->AddForce({ 0.0f, -150.0f });
    }
}

void Mob::UpdateMove(float dt)
{
    currentEventTime += dt;
    if (currentEventTime > eventTime)
    {
        currentEventTime = 0.0f;
        rigidbody->AddForce({ 0.0f, -150.0f });
    }
    SetPosition({ GetPosition().x + speed * dt, GetPosition().y });
}

void Mob::UpdateHit(float dt)
{
    currentHitTime += dt;
    if (currentHitTime > hitTime)
    {
        state = State::Move;
        update = std::bind(&Mob::UpdateMove, this, std::placeholders::_1);
        animator->SetEvent("Move");
        rigidbody->SetDrag(0.0f);
        rigidbody->SetVelocity({ 0.0f, 0.0f });
    }
}

void Mob::UpdateSuction(float dt)
{
    suctionTime += dt;
    SetPosition(Utils::Lerp(suctionStartPos, target->GetPosition(), suctionTime));
    if (suctionTime > 1.0f)
    {
        SetActive(false);
    }
}

void Mob::SetSuction(GameObject* target)
{
    if (state != State::Suction)
    {
        state = State::Suction;
        animator->SetEvent("Suction");
        this->target = target;
        suctionTime = 0.0f;
        suctionStartPos = GetPosition();
        ((Collider*)GetComponent(ComponentType::Collider))->SetTrigger(true);
        update = std::bind(&Mob::UpdateSuction, this, std::placeholders::_1);
    }
}

void Mob::Damage(const int& damage, const float hitAxisX)
{
    state = State::Hit;
    animator->SetEvent("Hit");
    update = std::bind(&Mob::UpdateHit, this, std::placeholders::_1);
    currentHitTime = 0.0f;
    rigidbody->SetDrag(0.7f);
    rigidbody->SetVelocity({ hitAxisX * 100.0f, 0.0f });
}

void Mob::OnCollisionEnter(Collider* col)
{
    if (col->GetGameObject().GetName() == "Ground" && animator->GetClipName() == "Jump")
    {
        animator->SetEvent("Idle");
    }
    if (col->GetGameObject().GetName() == "Kirby")
    {
        ((Playable*)&col->GetGameObject())->Damage(atk, col->GetGameObject().GetPosition().x < GetPosition().x ? -1.0f : 1.0f);
        RigidBody2D* rig = (RigidBody2D*)col->GetGameObject().GetComponent(ComponentType::RigidBody);
    }
}

void Mob::OnCollisionStay(Collider* col)
{
}