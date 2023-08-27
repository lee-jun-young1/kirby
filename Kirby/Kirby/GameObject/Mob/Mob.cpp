#include "stdafx.h"
#include "Mob.h"
#include <Suction.h>
#include "Utils.h"
#include <Playable.h>
#include "GenPoint.h"
#include <StatusUI.h>
#include <SceneManager.h>
#include <MobPool.h>
void Mob::Reset()
{
    SpriteGO::Reset();
    update = std::bind(&Mob::UpdateMove, this, std::placeholders::_1);
    SetPosition(position);
    currentHP = maxHP;

    outCameraEvent = [this]() {
        genPoint->MobRemove();
    };
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

void Mob::UpdateDeath(float dt)
{
    currentEventTime += dt;
    if (currentEventTime > 1.0f)
    {
        Variables::Score += score;

        StatusUI* ui = (StatusUI*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("StatusUI");
        ui->RefreshScore();

        genPoint->MobRemove();
    }
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
        genPoint->MobRemove();
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
    animator->SetEvent("Hit");
    currentHitTime = 0.0f;
    rigidbody->SetDrag(0.7f);
    rigidbody->SetVelocity({ hitAxisX * 100.0f, 0.0f });

    currentHP -= damage;

    if (currentHP <= 0.0f && state == State::Death)
    {
        state = State::Death;
        update = std::bind(&Mob::UpdateDeath, this, std::placeholders::_1);
        currentEventTime += 2.0f;
    }
    else if (currentHP <= 0.0f)
    {
        state = State::Death;
        update = std::bind(&Mob::UpdateDeath, this, std::placeholders::_1);
        currentEventTime = 0.0f;
    }
    else
    {
        state = State::Hit;
        update = std::bind(&Mob::UpdateHit, this, std::placeholders::_1);
    }
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
    }
}

void Mob::OnCollisionStay(Collider* col)
{
}