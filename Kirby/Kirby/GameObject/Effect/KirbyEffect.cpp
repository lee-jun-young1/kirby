#include "stdafx.h"
#include "KirbyEffect.h"
#include "Utils.h"
#include "RigidBody2D.h"
#include <Mob.h>

void KirbyEffect::StarShot(const float& direction)
{
	time = 0.0f;
	duration = 10.0f;
	targetAlpha = 255;
	speed = 1.0f;
	RigidBody2D* effectRig = (RigidBody2D*)GetComponent(ComponentType::RigidBody);
	effectRig->SetGravity(false);
	effectRig->SetVelocity({ direction * 300.0f, 0.0f });
}

void KirbyEffect::EmptyShot(const float& direction)
{
	time = 0.0f;
	duration = 1.0f;
	targetAlpha = 0;
	speed = 5.0f;
	RigidBody2D* effectRig = (RigidBody2D*)GetComponent(ComponentType::RigidBody);
	effectRig->SetGravity(false);
	effectRig->SetVelocity({ direction * 150.0f, 0.0f });
}

void KirbyEffect::Update(float dt)
{
	SpriteGO::Update(dt);
	time += dt * speed;
	duration -= dt * speed;
	sf::Color color = sprite.getColor();
	color.a = Utils::Lerp(255, targetAlpha, time, true);
	sprite.setColor(color);

	if (duration < 0.0f)
	{
		SetActive(false);
	}
}

void KirbyEffect::OnTriggerEnter(Collider* col)
{
	cout << duration << endl;
	if (col->GetGameObject().HasTag("Ground") && time > 0.1f)
	{
		SetActive(false);
	}
	if (col->GetGameObject().HasTag("Mob"))
	{
		((Mob*)&col->GetGameObject())->Damage(1.0f);
		SetActive(false);
	}
}
