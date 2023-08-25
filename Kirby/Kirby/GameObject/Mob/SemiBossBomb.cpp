#include "stdafx.h"
#include "SemiBossBomb.h"
#include <EffectPool.h>
#include <SceneManager.h>
#include <StatusUI.h>
#include "Utils.h"
#include <Camera.h>

void SemiBossBomb::Init()
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

	score = 1000;
}

void SemiBossBomb::OnDisable()
{
	if (currentHP <= 0)
	{
		Camera* camera = (Camera*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("Camera");
		camera->SetType(CameraType::Free);
	}
}

void SemiBossBomb::Reset()
{
	maxHP = 30;
	SpriteGO::Reset();
	update = std::bind(&Mob::UpdateIdle, this, std::placeholders::_1);
	rigidbody->SetMass(2.0f);
	currentHP = maxHP;
	//SetState(State::None);
	//SetState(State::Jump);

	inCameraEvent = [this]() {
		WakeUp();
	};
}

void SemiBossBomb::WakeUp()
{
	currentHP = maxHP;
	SetState(State::Jump);
}

void SemiBossBomb::Damage(const int& damage, const float hitAxisX)
{
	update = std::bind(&Mob::UpdateHit, this, std::placeholders::_1);
	currentHitTime = 0.0f;
	StatusUI* ui = (StatusUI*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("StatusUI");
	currentHP -= damage;
	ui->SetEnemyHP(currentHP / (float)maxHP);

	if (currentHP <= 0)
	{
		AddTag("Suctionable");
		animator->SetEvent("Death");
		SetState(State::Death);
		rigidbody->SetVelocity({0.0f, 0.0f});
	}
}

void SemiBossBomb::SetState(State state)
{
	sf::Vector2f playerPos = SCENE_MANAGER.GetCurrentScene()->FindGameObject("Kirby")->GetPosition();;
	SetFlipX((playerPos - GetPosition()).x > 0.0f);
	switch(state)
	{
	case State::None:
		break;
	case State::Jump:
		animator->SetEvent("Jump");
		onCollisionEnter = std::bind(&SemiBossBomb::JumpCollisionEnter, this, std::placeholders::_1);
		break;
	case State::TripleJump:
		animator->SetEvent("Jump");
		onCollisionEnter = std::bind(&SemiBossBomb::TripleJumpCollisionEnter, this, std::placeholders::_1);
		break;
	case State::Dash:
		animator->SetEvent("Dash");
		onCollisionEnter = nullptr;
		currentEventTime = 0.0f;
		rigidbody->SetGravity(false);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
		break;
	case State::Throw:
		animator->SetEvent("Throw");
		onCollisionEnter = std::bind(&SemiBossBomb::ThrowCollisionEnter, this, std::placeholders::_1);
		break;
	case State::TripleThrow:
		animator->SetEvent("TripleThrow");
		onCollisionEnter = std::bind(&SemiBossBomb::TripleThrowCollisionEnter, this, std::placeholders::_1);
		break;
	case State::Death:
		onCollisionEnter = std::bind(&SemiBossBomb::DeathCollisionEnter, this, std::placeholders::_1);
		break;
	case State::Suction:
		onCollisionEnter = nullptr;
		break;
	}
}

void SemiBossBomb::Update(float dt)
{
	if (animator->GetClipName() == "Dash")
	{
		currentEventTime += dt;
		if (currentEventTime > 1.0f)
		{
			rigidbody->SetGravity(true);
			SetState(State::Jump);
			currentEventTime = 0.0f;
		}
		else if(currentEventTime > 0.3f)
		{
			rigidbody->SetVelocity({sprite.getScale().x * 80.0f, 0.0f});
		}

	}
}


void SemiBossBomb::OnCollisionEnter(Collider* col)
{
	if (onCollisionEnter != nullptr)
	{
		onCollisionEnter(col);
	}
}

void SemiBossBomb::JumpCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y >= 0.0f)
	{
		rigidbody->SetVelocity({ jumpPower[0].x * scale.x, jumpPower[0].y });
		jumpPower[0].x *= -1.0f;
		jumpCount++;
		if (jumpCount > 7)
		{
			jumpCount = 0;
			SetState((State)Utils::RandomRange(1, 5));
			//SetState(State::Dash);
		}
	}
}

void SemiBossBomb::TripleJumpCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y >= 0.0f)
	{
		rigidbody->SetVelocity({ jumpPower[jumpCount / 2].x * scale.x,jumpPower[jumpCount / 2].y });
		jumpPower[jumpCount / 2].x *= -1.0f;
		jumpCount++;
		if (jumpCount > 5)
		{
			jumpCount = 0;
			SetState(State::Jump);
		}
	}
}

void SemiBossBomb::ThrowCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y >= 0.0f)
	{
		rigidbody->SetVelocity({ jumpPower[0].x * scale.x, jumpPower[0].y });
		jumpPower[0].x *= -1.0f;
		jumpCount++;
		if (jumpCount % 2 == 1)
		{
			BombEffect* bomb = effectPool->GetBombEffect(PhysicsLayer::EnemyEffect);
			bomb->sortLayer = 5;
			bomb->AddTag("Suctionable");
			bomb->SetPosition(GetPosition() - GetOrigin() + sf::Vector2f(0.0f, -20.0f));
			bomb->Ready();
			bomb->Fire({ throwPower[2].x * scale.x, throwPower[2].y });
			bomb = nullptr;
			//throwCount++;
			SetState(State::Jump);
		}
		if (jumpCount > 1)
		{
			jumpCount = 0;
		}
	}
}

void SemiBossBomb::TripleThrowCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y >= 0.0f)
	{
		rigidbody->SetVelocity(jumpPower[0]);
		jumpPower[0].x *= -1.0f;
		jumpCount++;
		if (jumpCount % 2 == 1)
		{
			BombEffect* bomb = effectPool->GetBombEffect(PhysicsLayer::EnemyEffect);
			bomb->sortLayer = 5;
			bomb->AddTag("Suctionable");
			bomb->SetPosition(GetPosition() - GetOrigin() + sf::Vector2f(0.0f, -20.0f));
			bomb->Ready();
			bomb->Fire({ throwPower[throwCount].x * scale.x, throwPower[throwCount].y });
			bomb = nullptr;
			throwCount++;
			if (throwCount > 2)
			{
				throwCount = 0;
				SetState(State::Jump);
			}
		}
		if (jumpCount > 1)
		{
			jumpCount = 0;
		}
	}
}
void SemiBossBomb::DeathCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Ground") && rigidbody->GetVelocity().y >= 0.0f)
	{
		rigidbody->SetVelocity({ 0.0f, 0.0f });
		rigidbody->SetGravity(false);
	}
}

void SemiBossBomb::OnCollisionStay(Collider* col)
{
}
