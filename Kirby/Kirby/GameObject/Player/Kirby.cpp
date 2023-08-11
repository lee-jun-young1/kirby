#include "stdafx.h"
#include "Kirby.h"
#include <SceneManager.h>
#include <Mob.h>

void Kirby::MoveKey(const sf::Vector2f& axis, const float& deltaTime)
{
	if (state == KirbyState::Idle || state == KirbyState::Balloon)
	{
		SetPosition(GetPosition() + axis * speed * deltaTime);
		SetFlipX(axis.x > 0.0f ? true : false);
		animator->SetEvent("PressMove");
	}
}

void Kirby::DashKey(const sf::Vector2f& axis, const float& deltaTime)
{
	if (state == KirbyState::Idle)
	{
		SetPosition(GetPosition() + axis * speed * 2.0f * deltaTime);
		SetFlipX(axis.x > 0.0f ? true : false);
		animator->SetEvent("Run");
	}
}

void Kirby::MoveKeyEnd()
{
	animator->SetEvent("Idle");
}

void Kirby::ChargeKey()
{
	if (state == KirbyState::Balloon)
	{
		//Fire
		ShotStar();
		
	}
	else
	{
		animator->SetEvent("PressX");
	}
}

void Kirby::ChargeKeyContinue()
{
	if (state == KirbyState::Idle || state == KirbyState::Suction)
	{
		state = KirbyState::Suction;
		animator->SetEvent("AbilityKeyContinue");
		suction->SetActive(true);
	}
}

void Kirby::ChargeKeyEnd()
{
	if (state == KirbyState::Suction)
	{
		state = KirbyState::Idle;
		animator->SetEvent("Idle");
		suction->SetActive(false);
	}
}

void Kirby::SitKey()
{
	if (state == KirbyState::Balloon)
	{
		Eat();
	}
	else
	{
		state = KirbyState::Sit;
		Sit();
	}
}

void Kirby::SitKeyEnd()
{
	state = KirbyState::Idle;
	animator->SetEvent("Idle");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });
}

void Kirby::JumpKey()
{
	animator->SetEvent("PressJump");
	//rigidbody->AddForce({ 0.0f, -150.0f });
}

void Kirby::SetAbility()
{
	ability = keepInMouseAbility;
	keepInMouseAbility = KirbyAbility::None;
	sf::Texture* tex = Resources.GetTexture(abilityTextureIDs[(int)ability]);
	if (tex != nullptr)
	{
		SetTexture(*tex);
		SetOrigin(origin);
	}
}

void Kirby::Eat()
{
	animator->SetEvent("Eat");
	SetAbility();
	state = KirbyState::Idle;
}

void Kirby::Sit()
{
	animator->SetEvent("PressSit");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 12.0f });
	collider->SetOffset({ -12.0f, -12.0f });
}

void Kirby::Init()
{
	abilityTextureIDs.push_back("sprites/kirby/Class_Normal.png");
	abilityTextureIDs.push_back("sprites/kirby/Class_Cutter.png");
	abilityTextureIDs.push_back("sprites/kirby/Class_Beam.png");
	abilityTextureIDs.push_back("sprites/kirby/Class_Bomb.png");
	SpriteGO::Init();
	animator = (Animator*)AddComponent(new Animator(*this, "animations/Kirby/Kirby", "Idle"));
	collider = (BoxCollider*)AddComponent(new BoxCollider(*this));
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });

	rigidbody = (RigidBody2D*)AddComponent(new RigidBody2D(*this));
	rigidbody->SetGravity(false);
	collider->SetRigidbody(rigidbody);
}

void Kirby::ShotStar() 
{
	animator->SetEvent("Shot");
	starEffect->SetActive(true);
	starEffect->SetPosition(GetPosition() - sf::Vector2f(0.0f, GetOrigin().y * 0.5f));
	keepInMouseAbility = KirbyAbility::None;
	state = KirbyState::Idle;
	RigidBody2D* effectRig = (RigidBody2D*)starEffect->GetComponent(ComponentType::RigidBody);
	effectRig->SetGravity(false);
	effectRig->SetVelocity({ GetScale().x * 300.0f, 0.0f });
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

	if (col->GetGameObject().GetName() == "Suctionable" && animator->GetClipName() == "Suction")
	{
		Mob* suctionable = (Mob*)&col->GetGameObject();
		keepInMouseAbility = suctionable->GetType();
		suctionable->SetActive(false);
		cout << "suction!!" << endl;
		cout << "keepInMouseAbility!!" << (int)keepInMouseAbility << endl;
		state = KirbyState::Balloon;
		animator->SetEvent("Balloon");
		suction->SetActive(false);
	}
}

void Kirby::VKey()
{
	SetAbility();
}
