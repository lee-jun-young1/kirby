#include "stdafx.h"
#include "Mushroom.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "GenPoint.h"
#include <SceneManager.h>
#include <MushroomHead.h>
#include <Playable.h>

void Mushroom::Init()
{
	Mob::Init();
	AddTag("Suctionable");
	AddTag("Mob");
	SetSize({ 24.0f, 24.0f });
	physicsLayer = (int)PhysicsLayer::Enemy;
	SetOrigin(Origins::BC);
	BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
	boxCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	boxCol->SetOffset({ 0.0f, -24.0f });
	RigidBody2D* rig = (RigidBody2D*)AddComponent(new RigidBody2D(*this));
	boxCol->SetRigidbody(rig);
	SetRigidBody(rig);

	SetOrigin({ 36.0f, 48.0f });
	boxCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	boxCol->SetOffset({ -12.0f, -24.0f });

	head = new MushroomHead("sprites/effects/mushroomHead.png", "MushroomHead");
	head->physicsLayer = (int)PhysicsLayer::EnemyEffect;
	head->AddTag("Suctionable");
	BoxCollider* headCol = (BoxCollider*)head->AddComponent(new BoxCollider(*head));
	headCol->SetRect({ 0.0f, 0.0f, 24.0f, 12.0f });
	RigidBody2D* headRig = (RigidBody2D*)head->AddComponent(new RigidBody2D(*head));
	headRig->SetGravity(false);
}

void Mushroom::UpdateIdle(float dt)
{
	currentEventTime += dt;
	if (currentEventTime > eventTime && hasHead)
	{
		hasHead = false;
		head->SetPosition(GetPosition() - sf::Vector2f(12.0f, 24.0f));
		RigidBody2D* headRig = (RigidBody2D*)head->GetComponent(ComponentType::RigidBody);
		//animator->SetEvent("Jump");
		currentEventTime = 0.0f;
		animator->SetEvent("ShootCap");
		head->SetActive(true);
		headRig->SetGravity(true);
		headRig->AddForce({ 0.0f, -150.0f });
	}
}


void Mushroom::Reset()
{
	SpriteGO::Reset();
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(head);
	update = std::bind(&Mushroom::UpdateIdle, this, std::placeholders::_1);
	SetPosition(position);
	currentHP = maxHP;

	outCameraEvent = [this]() {
		genPoint->MobRemove();
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(head);
	};
	head->Reset();
	RigidBody2D* headRig = (RigidBody2D*)head->GetComponent(ComponentType::RigidBody);
	headRig->SetVelocity({0.0f, 0.0f});
	headRig->SetGravity(false);
	head->SetActive(true);
	hasHead = true;
}


void Mushroom::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Ground" && animator->GetClipName() == "Jump")
	{
		animator->SetEvent("JumpWithCap");
	}
	if (col->GetGameObject().GetName() == "Kirby")
	{
		((Playable*)&col->GetGameObject())->Damage(atk, col->GetGameObject().GetPosition().x < GetPosition().x ? -1.0f : 1.0f);
	}
	if (col->GetGameObject().GetName() == "MushroomHead" && ((RigidBody2D*)col->GetGameObject().GetComponent(ComponentType::RigidBody))->GetVelocity().y > 0.0f)
	{
		hasHead = true;
		animator->SetEvent("JumpWithCap");
		RigidBody2D* headRig = (RigidBody2D*)head->GetComponent(ComponentType::RigidBody);
		headRig->SetVelocity({ 0.0f, 0.0f });
		headRig->SetGravity(false);
		head->SetActive(false);
	}
}