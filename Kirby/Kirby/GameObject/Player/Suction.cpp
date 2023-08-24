#include "stdafx.h"
#include "Kirby.h"
#include <Utils.h>
#include "Mob.h"
#include "Suction.h"

void Suction::Update(float dt)
{
	SetPosition(kirby->GetPosition() + sf::Vector2f(12.0f + (kirby->GetScale().x * 24.0f), 0.0f));
}
void Suction::OnEnable()
{
	suctionList.clear();
}

void Suction::OnDisable()
{
	for (auto go : suctionList)
	{
		if (go->HasTag("Mob"))
		{
			Mob* mob = dynamic_cast<Mob*>(go);
			kirby->SetInMouseType(mob->GetType());
			go->SetActive(false);
		}
		else
		{
			kirby->SetInMouseType(KirbyAbility::None);
			go->SetActive(false);
		}
	}
}



void Suction::OnTriggerStay(Collider* col)
{
	GameObject* go = &col->GetGameObject();
	if (go != nullptr && go->HasTag("Suctionable"))
	{
		for (auto suction : suctionList)
		{
			if (suction == go)
			{
				return;
			}
		}
		RigidBody2D* rig = (RigidBody2D*)go->GetComponent(ComponentType::RigidBody);
		if (rig != nullptr)
		{
			rig->SetVelocity((kirby->GetPosition() + sf::Vector2f(0.0f, -12.0f)) - col->GetCenter());
			rig->SetGravity(false);
		}
		suctionList.push_back(go);
		if (go->HasTag("Mob"))
		{
			Mob* mob = dynamic_cast<Mob*>(go);
			mob->SetSuction(kirby);
		}
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