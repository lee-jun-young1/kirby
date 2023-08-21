#include "stdafx.h"
#include "CutterEffect.h"
#include <Mob.h>
#include "EffectPool.h"

void CutterEffect::Update(float dt)
{
	rigidbody->SetVelocity({ turned ? rigidbody->GetVelocity().x + startPower * dt : rigidbody->GetVelocity().x - startPower * dt, rigidbody->GetVelocity().y });
	if (!turned && abs(rigidbody->GetVelocity().x) > abs(startPower))
	{
		turned = true;
	}
	else if (turned && abs(rigidbody->GetVelocity().x) > abs(startPower * 2.0f))
	{
		Return();
	}
	time += dt;
}

void CutterEffect::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground"))
	{
		if (rigidbody->GetGravity())
		{
			Return(true);
			rigidbody->SetGravity(false);
		}
		else
		{
			rigidbody->SetVelocity({ rigidbody->GetVelocity().x * -1.0f, rigidbody->GetVelocity().y });
			rigidbody->SetGravity(true);
		}
	}
	if (col->GetGameObject().HasTag("Mob"))
	{
		((Mob*)&col->GetGameObject())->Damage(1.0f, col->GetGameObject().GetPosition().x < GetPosition().x + sprite.getGlobalBounds().width * 0.5f ? -1.0f : 1.0f);
		SetActive(false);
	}
}

void CutterEffect::Fire(sf::Vector2f axis)
{
	turned = false;
	time = 0.0f;
	startPower = axis.x * 200.0f;
	rigidbody->SetVelocity({ startPower, 0.0f });
}

void CutterEffect::Return(bool forced)
{
	if (forced || time > 0.2f)
	{
		pool->ReturnCutterEffect(this);
	}
}
