#include "stdafx.h"
#include "MobPool.h"
#include "SceneManager.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "Animator.h"

Cutter* MobPool::GetCutter()
{
	Cutter* mob = cutters.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Cutter/Cutter", "Idle"));
	mob->SetAnimator(ani);
	mob->SetActive(true);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Bomb* MobPool::GetBomb()
{
	Bomb* mob = bombs.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Bomb/Bomb", "Jump"));
	mob->SetAnimator(ani);
	mob->SetActive(true);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

Beam* MobPool::GetBeam()
{
	Beam* mob = beams.Get();
	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Beam/Beam", "Move"));
	mob->SetAnimator(ani);
	mob->SetActive(false);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

void MobPool::ClearAllPool()
{
	for (auto mob : cutters.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	for (auto mob : mobs.GetUseList())
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
	for (auto mob : semiBossBombs.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}

	mobs.Clear();
	cutters.Clear();
	semiBossBombs.Clear();
	bombs.Clear();
	beams.Clear();
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
	cutters.Init(20);
	//semiBossBombs.Init(2);
	bombs.Init(10);
	beams.Init(10);
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
