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
	mob->SetActive(false);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	return mob;
}

//Bomb* MobPool::GetBomb()
//{
//	Bomb* mob = bombs.Get();
//	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Bomb/Bomb", "Idle"));
//	mob->SetAnimator(ani);
//	mob->SetActive(false);
//	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
//	return mob;
//}

//Beam* MobPool::GetBeam()
//{
//	Beam* mob = beams.Get();
//	Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Beam/Beam", "Idle"));
//	mob->SetAnimator(ani);
//	mob->SetActive(false);
//	SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
//	return mob;
//}

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
	for (auto mob : semiBossBombs.GetUseList())
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	}
	mobs.Clear();
	cutters.Clear();
	semiBossBombs.Clear();
}

void MobPool::Init()
{
	GameObject::Init();
	cutters.OnCreate = [this](Cutter* mob) {
		//mob->AddTag("Suctionable");
		//mob->AddTag("Mob");
		//mob->SetSize({ 24.0f, 24.0f });
		//mob->physicsLayer = (int)PhysicsLayer::Enemy;
		//mob->SetOrigin(Origins::BC);
		//BoxCollider* suctionAbleCol = (BoxCollider*)mob->AddComponent(new BoxCollider(*mob));
		//suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		//suctionAbleCol->SetOffset({ 0.0f, -24.0f });
		//RigidBody2D* rig = (RigidBody2D*)mob->AddComponent(new RigidBody2D(*mob));
		//suctionAbleCol->SetRigidbody(rig);
		//mob->SetRigidBody(rig);

		//mob->Reset();
		//mob->SetOrigin({ 36.0f, 48.0f });
		//mob->SetPosition(-10.0f, 0.0f);
		//suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		//suctionAbleCol->SetOffset({ -12.0f, -24.0f });
	};

	cutters.Init(20);
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
