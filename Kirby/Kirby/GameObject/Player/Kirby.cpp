#include "stdafx.h"
#include "Kirby.h"

void Kirby::Move(const sf::Vector2f& axis, const float& deltaTime)
{
	SetPosition(GetPosition() + axis * speed * deltaTime);
	SetFlipX(axis.x > 0.0f ? true : false);
	animator->SetEvent("PressMove");
}

void Kirby::Dash(const sf::Vector2f& axis, const float& deltaTime)
{
	SetPosition(GetPosition() + axis * speed * 2.0f * deltaTime);
	SetFlipX(axis.x > 0.0f ? true : false);
	animator->SetEvent("Run");
}

void Kirby::MoveEnd()
{
	animator->SetEvent("Idle");
}

void Kirby::Charge()
{
	animator->SetEvent("PressX");
}

void Kirby::ChargeEnd()
{
	animator->SetEvent("Idle");
}

void Kirby::Sit()
{
	animator->SetEvent("PressSit");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 12.0f });
	collider->SetOffset({ -12.0f, -12.0f });
}

void Kirby::SitEnd()
{
	animator->SetEvent("Idle");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });
}

void Kirby::Jump()
{
	animator->SetEvent("PressJump");
	rigidbody->AddForce({ 0.0f, -150.0f });
}

void Kirby::Init()
{
	SpriteGO::Init();
	animator = (Animator*)AddComponent(new Animator(*this, "animations/Kirby/Kirby", "Idle"));
	collider = (BoxCollider*)AddComponent(new BoxCollider(*this));
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });
	rigidbody = (RigidBody2D*)AddComponent(new RigidBody2D(*this));
	collider->SetRigidbody(rigidbody);
}

void Kirby::Release()
{
	SpriteGO::Release();
}

void Kirby::Reset()
{
	SpriteGO::Reset();
	SetOrigin({ 36.0f, 48.0f});
}

void Kirby::Update(float dt)
{
	SpriteGO::Update(dt);
}

void Kirby::Draw(sf::RenderWindow& window)
{
	SpriteGO::Draw(window);
}


void Kirby::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Ground" && animator->GetClipName() == "Jump")
	{
		animator->SetEvent("Idle");
	}
}