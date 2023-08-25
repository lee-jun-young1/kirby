#include "stdafx.h"
#include "MobPool.h"
#include "SceneManager.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "Animator.h"

Mob* MobPool::GetMob(EnemyType type)
{
	switch (type)
	{
	case EnemyType::None:
		break;
	case EnemyType::Cutter:
		return GetCutter();
		break;
	case EnemyType::Beam:
		return GetBeam();
		break;
	case EnemyType::Bomb:
		return GetBomb();
		break;
	case EnemyType::Bear:
		return GetBear();
		break;
	case EnemyType::Chick:
		return GetChick();
		break;
	case EnemyType::Fly:
		return GetFly();
		break;
	case EnemyType::Mushroom:
		return GetMushroom();
		break;
	case EnemyType::Normal:
		return GetNormal();
		break;
	case EnemyType::SB_Bomb:
		return GetSemiBossBomb();
		break;
	case EnemyType::Wood:
		//작업 필요
		break;
	default:
		break;
	}

	return nullptr;
}

void MobPool::MobReturn(Mob* mob)
{
	EnemyType type = mob->GetEnemyType();
	SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);

	switch (type)
	{
	case EnemyType::None:
		break;
	case EnemyType::Cutter:
		cutters.Return((Cutter*)mob);
		break;
	case EnemyType::Beam:
		beams.Return((Beam*)mob);
		break;
	case EnemyType::Bomb:
		bombs.Return((Bomb*)mob);
		break;
	case EnemyType::Bear:
		bears.Return((Bear*)mob);
		break;
	case EnemyType::Chick:
		chicks.Return((Chick*)mob);
		break;
	case EnemyType::Fly:
		flies.Return((Fly*)mob);
		break;
	case EnemyType::Mushroom:
		mushrooms.Return((Mushroom*)mob);
		break;
	case EnemyType::Normal:
		normals.Return((Normal*)mob);
		break;
	case EnemyType::SB_Bomb:
		semiBossBombs.Return((SemiBossBomb*)mob);
		break;
	case EnemyType::Wood:
		//작업 필요
		break;
	default:
		break;
	}
}

void MobPool::ClearAllPool()
{
	for (auto mob : cutters.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : bombs.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : beams.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : normals.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : flies.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : bears.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : chicks.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : mushrooms.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : semiBossBombs.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}

	cutters.Clear();
	bombs.Clear();
	beams.Clear();
	normals.Clear();
	flies.Clear();
	bears.Clear();
	chicks.Clear();
	mushrooms.Clear();
	semiBossBombs.Clear();
}

void MobPool::Init()
{
	GameObject::Init();
	cutters.OnCreate = [this](Cutter* mob)
	{
	};
	bombs.OnCreate = [this](Bomb* mob)
	{
	};
	beams.OnCreate = [this](Beam* mob)
	{
	};
	normals.OnCreate = [this](Normal* mob) 
	{
	};
	flies.OnCreate = [this](Fly* mob) 
	{
	};
	bears.OnCreate = [this](Bear* mob) 
	{
	};
	chicks.OnCreate = [this](Chick* mob) 
	{
	};
	mushrooms.OnCreate = [this](Mushroom* mob) 
	{
	};
	semiBossBombs.OnCreate = [this](SemiBossBomb* mob) 
	{
	};


	cutters.Init(10);
	bombs.Init(10);
	beams.Init(10);
	normals.Init(10);
	flies.Init(10);
	bears.Init(10);
	chicks.Init(10);
	mushrooms.Init(10);
	semiBossBombs.Init(10);
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


Cutter* MobPool::GetCutter()
{
	Cutter* mob = cutters.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Cutter/Cutter", "Idle"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Bomb* MobPool::GetBomb()
{
	Bomb* mob = bombs.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Bomb/Bomb", "Jump"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Beam* MobPool::GetBeam()
{
	Beam* mob = beams.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Beam/Beam", "Move"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Normal* MobPool::GetNormal()
{
	Normal* mob = normals.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Normal/Normal", "Move"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Fly* MobPool::GetFly()
{
	Fly* mob = flies.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Fly/Fly", "Fly"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Bear* MobPool::GetBear()
{
	Bear* mob = bears.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Bear/Bear", "Jump"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Chick* MobPool::GetChick()
{
	Chick* mob = chicks.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Chick/Chick", "Idle"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Mushroom* MobPool::GetMushroom()
{
	Mushroom* mob = mushrooms.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Mushroom/Mushroom", "JumpWithCap"));
	mob->SetAnimator(ani);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

SemiBossBomb* MobPool::GetSemiBossBomb()
{
	SemiBossBomb* mob = semiBossBombs.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/SB-Bomb/SB-Bomb", "Jump"));
	mob->SetAnimator(ani);
	mob->SetEffectPool((EffectPool*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("EffectPool"));
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}