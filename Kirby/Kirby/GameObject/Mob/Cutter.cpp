#include "stdafx.h"
#include "Cutter.h"

void Cutter::Reset()
{
    Mob::Reset();
    update = std::bind(&Cutter::UpdateIdle, this, std::placeholders::_1);
}


void Cutter::UpdateIdle(float dt)
{
    currentEventTime += dt;
    if (currentEventTime > eventTime)
    {
        currentEventTime = 0.0f;
        rigidbody->AddForce({ 0.0f, -150.0f });
    }
    else if (currentEventTime > eventTime - 0.5f)
    {
        animator->SetEvent("Jump");
    }
}


void Cutter::UpdateHit(float dt)
{
    currentHitTime += dt;
    if (currentHitTime > hitTime)
    {
        state = State::Idle;
        update = std::bind(&Cutter::UpdateIdle, this, std::placeholders::_1);
        animator->SetEvent("Idle");
        rigidbody->SetDrag(0.0f);
        rigidbody->SetVelocity({ 0.0f, 0.0f });
    }
}


void Cutter::Damage(const int& damage, const float hitAxisX)
{
    state = State::Hit;
    animator->SetEvent("Hit");
    update = std::bind(&Cutter::UpdateHit, this, std::placeholders::_1);
    currentHitTime = 0.0f;
    rigidbody->SetDrag(0.7f);
    rigidbody->SetVelocity({ hitAxisX * 100.0f, 0.0f });
}