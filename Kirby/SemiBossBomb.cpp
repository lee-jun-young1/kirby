#include "stdafx.h"
#include "SemiBossBomb.h"
#include <EffectPool.h>

void SemiBossBomb::Reset()
{
	SpriteGO::Reset();
	update = std::bind(&Mob::UpdateIdle, this, std::placeholders::_1);
	SetPosition(regenPosition);
	rigidbody->SetMass(2.0f);
}

void SemiBossBomb::Damage(const int& damage, const float hitAxisX)
{
	state = State::Hit;
	animator->SetEvent("Hit");
	update = std::bind(&Mob::UpdateHit, this, std::placeholders::_1);
	currentHitTime = 0.0f;
}

void SemiBossBomb::UpdateIdle(float dt)
{

}

void SemiBossBomb::UpdateMove(float dt)
{
}

void SemiBossBomb::UpdateThrow(float dt)
{
}

void SemiBossBomb::UpdateTripleThrow(float dt)
{
}

void SemiBossBomb::UpdateHit(float dt)
{
}

void SemiBossBomb::UpdateSuction(float dt)
{
}

void SemiBossBomb::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y >= 0.0f)
	{
		//rigidbody->SetVelocity(jumpPower[jumpCount / 2]);
		rigidbody->SetVelocity(jumpPower[0]);
		//jumpPower[jumpCount / 2].x *= -1.0f;
		jumpPower[0].x *= -1.0f;
		jumpCount++;
		if (jumpCount % 2 == 1)
		{
			BombEffect* bomb = effectPool->GetBombEffect(PhysicsLayer::EnemyEffect);
			bomb->sortLayer = 5;
			bomb->AddTag("Suctionable");
			bomb->SetPosition(GetPosition() - GetOrigin() + sf::Vector2f(0.0f, -20.0f));
			bomb->Ready();
			bomb->Fire(throwPower[throwCount]);
			bomb = nullptr;
			cout << throwCount << endl;
			throwCount++;
			if (throwCount > 2)
			{
				throwCount = 0;
			}
		}
		if (jumpCount > 5)
		{
			jumpCount = 0;
		}
	}
}

void SemiBossBomb::OnCollisionStay(Collider* col)
{
}
