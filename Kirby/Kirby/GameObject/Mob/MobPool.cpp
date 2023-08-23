#include "stdafx.h"
#include "MobPool.h"
#include "SceneManager.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "Animator.h"

Mob* MobPool::GetMob(const EnemyType& type)
{
	KirbyAbility ability = KirbyAbility::None;
	std::string texturePath;
	std::string animationPath;
	std::string defaultAction = "Move";
	bool isSuctionAble = true;
	switch (type)
	{
	case EnemyType::Cutter:
	{
		ability = KirbyAbility::Cutter;
		texturePath = "sprites/mob/mob_Cutter.png";
		animationPath = "animations/Mob/Cutter/Cutter";
		defaultAction = "Jump";
	}
		break;
	case EnemyType::Beam:
	{
		ability = KirbyAbility::Beam;
		texturePath = "sprites/mob/Mob_Beam.png";
		animationPath = "animations/Mob/Beam/Beam";
	}
		break;
	case EnemyType::Bomb:
	{
		ability = KirbyAbility::Bomb;
		texturePath = "sprites/mob/mob_Bomb.png";
		animationPath = "animations/Mob/Bomb/Bomb";
		defaultAction = "Jump";
	}
		break;
	case EnemyType::Bear:
	{
		texturePath = "sprites/mob/Mob_Bear.png";
		animationPath = "animations/Mob/Bear/Bear";
		defaultAction = "Jump";
	}
		break;
	case EnemyType::Chick:
	{
		texturePath = "sprites/mob/Mob_chick.png";
		animationPath = "animations/Mob/Chick/Chick";
		defaultAction = "Idle";
	}
		break;
	case EnemyType::Normal:
	{
		texturePath = "sprites/mob/mob_normal.png";
		animationPath = "animations/Mob/Normal/Normal";
	}
		break;
	case EnemyType::Fly:
	{
		texturePath = "sprites/mob/Mob_Fly.png";
		animationPath = "animations/Mob/Fly/Fly";
		defaultAction = "Fly";
	}
		break;
	case EnemyType::Mushroom:
	{
		texturePath = "sprites/mob/Mob_mushroom.png";
		animationPath = "animations/Mob/Mushroom/Mushroom";
		defaultAction = "Jump";
	}
		break;
	case EnemyType::SB_Bomb:
	{
		ability = KirbyAbility::Bomb;
		texturePath = "sprites/mob/SB_Bomb.png";
		animationPath = "animations/Mob/SB-Bomb/SB-Bomb";
		defaultAction = "Jump";
		isSuctionAble = false;
	}
		break;
	case EnemyType::Wood:
	{
		texturePath = "sprites/mob/Boss_Wood.png";
		animationPath = "animations/Mob/Wood/Wood";
		defaultAction = "Idle";
		isSuctionAble = false;
	}
		break;
	default:
		break;
	}
	Mob* mob = mobs.Get();
	if (isSuctionAble)
	{
		mob->AddTag("Suctionable");
	}
	mob->SetType(ability);
	mob->SetTextureID(texturePath);

	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, animationPath, defaultAction));
	mob->SetAnimator(ani);
	mob->SetActive(false);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

void MobPool::ClearPool()
{
	for (auto mob : mobs.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	mobs.Clear();
}

void MobPool::Init()
{
	GameObject::Init();
	mobs.OnCreate = [this](Mob* mob) {
		mob->SetName("Mob");
		mob->AddTag("Mob");
		mob->physicsLayer = (int)PhysicsLayer::Enemy;

		BoxCollider* mobCol = (BoxCollider*)mob->AddComponent(new BoxCollider(*mob));
		mobCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		mobCol->SetOffset({ -12.0f, -24.0f });

		RigidBody2D* rig = (RigidBody2D*)mob->AddComponent(new RigidBody2D(*mob));
		mobCol->SetRigidbody(rig);
		mob->SetRigidBody(rig);
		mob->SetOrigin({ 36.0f, 48.0f });
	};
	mobs.Init(30);
}

void MobPool::Release()
{
	GameObject::Release();
}

void MobPool::Reset()
{
	GameObject::Reset();
}

void MobPool::Update(float dt)
{
	GameObject::Update(dt);
}

void MobPool::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}
