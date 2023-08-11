#include "stdafx.h"
#include "Suction.h"
#include "Kirby.h"
#include <Utils.h>
#include <Mob.h>

void Suction::Update(float dt)
{
	SetPosition(kirby->GetPosition() + sf::Vector2f(12.0f + (kirby->GetScale().x * 24.0f), 0.0f));
}

void Suction::OnTriggerEnter(Collider* col)
{
	Mob* mob = dynamic_cast<Mob*>(&col->GetGameObject());
	if (mob != nullptr && mob->IsSuctionable())
	{
		RigidBody2D* rig = ((RigidBody2D*)col->GetGameObject().GetComponent(ComponentType::RigidBody));
		if (rig != nullptr)
		{
			rig->AddForce(Utils::Normalize(kirby->GetPosition() - col->GetGameObject().GetPosition()) * suctionPower);
		}
	}
}

void Suction::Init()
{
	physicsLayer = (int)PhysicsLayer::Player;
	collider = (BoxCollider*)AddComponent(new BoxCollider(*this));
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -24.0f, -24.0f });
	collider->SetTrigger(true);
}