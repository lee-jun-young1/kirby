#include "stdafx.h"
#include "BombEffect.h"
#include "RigidBody2D.h"
#include "EffectPool.h"
#include <Mob.h>
#include <Kirby.h>

void BombEffect::Update(float deltaTime)
{
	if (animator->GetClipName() == "BoomEnd")
	{
		cout << "Return!!" << endl;
		pool->ReturnBombEffect(this);
	} 
	else if (animator->GetClipName() == "Boom")
	{
		animator->SetEvent("");
		collider->SetTrigger(true);
		collider->GetRigidBody()->SetGravity(false);
		collider->SetRect({ 0.0f, 0.0f, 72.0f, 72.0f });
		collider->SetOffset({ 0.0f, 0.0f });
	}
	else if (animator->GetClipName() == "Ready")
	{
		animator->SetEvent("");
	}
}

void BombEffect::OnTriggerEnter(Collider* col)
{
	if (physicsLayer == (int)PhysicsLayer::PlayerEffect && col->GetGameObject().HasTag("Mob") && animator->GetClipName() == "Ready")
	{
		collider->GetRigidBody()->SetVelocity({ 0.0f, 0.0f });
		collider->GetRigidBody()->SetGravity(false);
		animator->SetEvent("Boom");
	}
	else if (col->GetGameObject().HasTag("Ground") && animator->GetClipName() == "Ready")
	{
		if (col->GetNormal(collider->GetCenter()).y == 0.0f)
		{
			collider->GetRigidBody()->SetVelocity({ 0.0f, 0.0f });
			collider->GetRigidBody()->SetGravity(false);
			animator->SetEvent("Boom");
		}
		else
		{
			lastForce *= 0.7f;
			if (lastForce.y > -30.0f)
			{
				collider->GetRigidBody()->SetVelocity({0.0f, 0.0f});
				collider->GetRigidBody()->SetGravity(false);
			}
			else
			{
				collider->GetRigidBody()->SetVelocity(lastForce);
			}
		}
	}
}

void BombEffect::OnTriggerStay(Collider* col)
{
	if (col->GetGameObject().HasTag("Mob") && animator->GetClipName() != "Ready")
	{
		((Mob*)&col->GetGameObject())->Damage(1.0f, col->GetGameObject().GetPosition().x < GetPosition().x + sprite.getGlobalBounds().width * 0.5f ? -1.0f : 1.0f);
	}
	if (col->GetGameObject().HasTag("Kirby") && animator->GetClipName() != "Ready")
	{
		((Kirby*)&col->GetGameObject())->Damage(1.0f, col->GetGameObject().GetPosition().x < GetPosition().x + sprite.getGlobalBounds().width * 0.5f ? -1.0f : 1.0f);
	}
}

void BombEffect::Fire(const sf::Vector2f& force)
{
	lastForce = force;
	collider->GetRigidBody()->SetGravity(true);
	collider->GetRigidBody()->AddForce(force);
}

void BombEffect::RunFire(const sf::Vector2f& force)
{
	collider->GetRigidBody()->SetGravity(false);
	collider->GetRigidBody()->AddForce(force);
}


void BombEffect::Ready()
{
	animator->SetState("Ready");
	collider->SetTrigger(true);
	collider->SetRect({ 0.0f, 0.0f, 20.0f, 20.0f });
	collider->SetOffset({ 24.0f, 24.0f });
	collider->GetRigidBody()->SetVelocity({0.0f, 0.0f});
	collider->GetRigidBody()->SetGravity(false);
}