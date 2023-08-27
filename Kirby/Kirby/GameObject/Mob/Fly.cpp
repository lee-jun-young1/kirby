#include "stdafx.h"
#include "Fly.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "GenPoint.h";

void Fly::Init()
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
}

void Fly::UpdateMove(float dt)
{
	if (rigidbody->GetVelocity().y < -120.0f)
	{
		rigidbody->SetMass(1.0f);
	}
	if (rigidbody->GetVelocity().y > 120.0f)
	{
		rigidbody->SetMass(-1.0f);
	}
	SetPosition({ GetPosition().x + speed * dt, GetPosition().y });
}


void Fly::Reset()
{
	SpriteGO::Reset();
	update = std::bind(&Mob::UpdateMove, this, std::placeholders::_1);
	SetPosition(position);
	currentHP = maxHP;

	outCameraEvent = [this]() {
		genPoint->MobRemove();
	};
}