#include "stdafx.h"
#include "BombEffect.h"
#include "RigidBody2D.h"
#include "EffectPool.h"
#include <Mob.h>

void BombEffect::Update(float deltaTime)
{
	cout << animator->GetClipName() << endl;
	if (animator->GetClipName() == "BoomEnd")
	{
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
}

void BombEffect::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Mob") && animator->GetClipName() == "Ready")
	{
		animator->Seek(237);
	}
	else if (col->GetGameObject().HasTag("Ground") && animator->GetClipName() == "Ready")
	{
		collider->SetTrigger(false);
	}
}

void BombEffect::OnTriggerStay(Collider* col)
{
	if (col->GetGameObject().HasTag("Mob"))
	{
		((Mob*)&col->GetGameObject())->Damage(1.0f, col->GetGameObject().GetPosition().x < GetPosition().x + sprite.getGlobalBounds().width * 0.5f ? -1.0f : 1.0f);
		SetActive(false);
	}
}

void BombEffect::Fire(float bombTime)
{
	collider->SetRect({ 0.0f, 0.0f, 20.0f, 20.0f });
	collider->SetOffset({ 24.0f, 24.0f });
	collider->GetRigidBody()->SetGravity(true);
	collider->SetTrigger(true);
	time = 0.0f;
	this->bombTime = bombTime;
}
