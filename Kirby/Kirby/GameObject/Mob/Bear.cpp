#include "stdafx.h"
#include "Bear.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "GenPoint.h"

void Bear::Init()
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

void Bear::UpdateMove(float dt)
{
	currentEventTime += dt;
	if (currentEventTime > eventTime && !isRun)
	{
		currentEventTime = 3.0f;
		animator->SetEvent("Rush");
		isRun = true;
	}
	else if (currentEventTime > eventTime && isRun)
	{
		currentEventTime = 0.0f;
		animator->SetEvent("Jump");
		isRun = false;
	}
	SetPosition({ GetPosition().x + (isRun ? 4.0f : 1.0f) * speed * dt , GetPosition().y });
}

void Bear::Reset()
{
	SpriteGO::Reset();
	update = std::bind(&Bear::UpdateMove, this, std::placeholders::_1);
	SetPosition(position);
	currentHP = maxHP;

	currentEventTime = 0.0f;
	isRun = false;

	outCameraEvent = [this]() {
		genPoint->MobRemove();
	};
}