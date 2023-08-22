#include "stdafx.h"
#include "MobPool.h"
#include "SceneManager.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "Animator.h"

Mob* MobPool::GetMob(const EnemyType& type)
{
	//Mob* mob = mobs.Get();
	//mob->SetActive(false);
	//mob->physicsLayer = (int)PhysicsLayer::Enemy;
	//mob->SetActive(true);
	//SCENE_MANAGER.GetCurrentScene()->AddGameObject(mob);
	//return mob;
	return nullptr;
}

void MobPool::ReturnMob(Mob* mob)
{
	SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(mob);
	mobs.Return(mob);
}

void MobPool::Init()
{
	GameObject::Init();
	mobs.OnCreate = [this](Mob* mob) {
		mob->AddTag("Suctionable");
		mob->AddTag("Mob");
		mob->SetSize({24.0f, 24.0f});
		mob->physicsLayer = (int)PhysicsLayer::Enemy;

		BoxCollider* mobCol = (BoxCollider*)mob->AddComponent(new BoxCollider(*mob));
		mobCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		mobCol->SetOffset({ -12.0f, -24.0f });

		RigidBody2D* rig = (RigidBody2D*)mob->AddComponent(new RigidBody2D(*mob));
		mobCol->SetRigidbody(rig);

		Animator* ani = (Animator*)mob->AddComponent(new Animator(*mob, "animations/Mob/Normal/Normal", "Move"));
		mob->SetAnimator(ani);
		mob->SetRigidBody(rig);

		mob->sortLayer = 1;
		mob->SetOrigin({ 36.0f, 48.0f });
		mob->SetRegenPosition(position);
	};
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
