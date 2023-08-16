#include "stdafx.h"
#include "Kirby.h"
#include <Utils.h>
#include "Mob.h"
#include "Suction.h"

void Suction::Update(float dt)
{
	SetPosition(kirby->GetPosition() + sf::Vector2f(12.0f + (kirby->GetScale().x * 24.0f), 0.0f));
}



void Suction::OnTriggerStay(Collider* col)
{
	Mob* mob = dynamic_cast<Mob*>(&col->GetGameObject());
	if (mob != nullptr && mob->IsSuctionable())
	{
		mob->SetSuction(kirby);
	}
}

void Suction::Init()
{
	physicsLayer = (int)PhysicsLayer::Player;
	collider = (BoxCollider*)AddComponent(new BoxCollider(*this));
	collider->SetRect({ 0.0f, 0.0f, 20.0f, 20.0f });
	collider->SetOffset({ -22.0f, -22.0f });
	collider->SetTrigger(true);
}