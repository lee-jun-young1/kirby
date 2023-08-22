#include "stdafx.h"
#include "EffectPool.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include <SceneManager.h>

CutterEffect* EffectPool::GetCutterEffect(const PhysicsLayer& layer)
{
	CutterEffect* effect = cutterEffects.Get();
	effect->SetActive(false);
	effect->physicsLayer = (int)layer;
	effect->SetActive(true);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(effect);
	return effect;
}
BeamEffect* EffectPool::GetBeamEffect(const PhysicsLayer& layer)
{
	BeamEffect* effect = beamEffects.Get();
	effect->SetActive(false);
	effect->physicsLayer = (int)layer;
	effect->SetActive(true);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(effect);
	return effect;
}
BombEffect* EffectPool::GetBombEffect(const PhysicsLayer& layer)
{
	BombEffect* effect = bombEffects.Get();
	effect->SetActive(false);
	effect->physicsLayer = (int)layer;
	effect->SetActive(true);
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(effect);
	return effect;
}

void EffectPool::ReturnCutterEffect(CutterEffect* effect)
{
	SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(effect);
	cutterEffects.Return(effect);
}

void EffectPool::ReturnBeamEffect(BeamEffect* effect)
{
	SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(effect);
	beamEffects.Return(effect);
}

void EffectPool::ReturnBombEffect(BombEffect* effect)
{
	SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(effect);
	bombEffects.Return(effect);
}

void EffectPool::Init()
{
	GameObject::Init();
	cutterEffects.OnCreate = [this](CutterEffect* effect)
	{
		BoxCollider* col = (BoxCollider*)effect->AddComponent(new BoxCollider(*effect));
		RigidBody2D* rig = (RigidBody2D*)effect->AddComponent(new RigidBody2D(*effect));
		col->SetRect({ 0.0f, 0.0f, 20.0f, 20.0f });
		col->SetOffset({ 24.0f, 24.0f });
		col->SetTrigger(true);
		col->SetRigidbody(rig);
		rig->SetGravity(false);
		effect->SetRigidbody(rig);
		effect->SetPool(this);
		effect->AddComponent(new Animator(*effect, "animations/Effect/Cutter/Cutter", "Shot"));
		effect->AddTag("CutterEffect");
	};
	beamEffects.OnCreate = [this](BeamEffect* effect)
	{
		BoxCollider* col = (BoxCollider*)effect->AddComponent(new BoxCollider(*effect));
		RigidBody2D* rig = (RigidBody2D*)effect->AddComponent(new RigidBody2D(*effect));
		col->SetRect({ 0.0f, 0.0f, 8.0f, 8.0f });
		col->SetOffset({ 32.0f, 32.0f });
		col->SetTrigger(true);
		col->SetRigidbody(rig);
		rig->SetGravity(false);
		Animator* ani = (Animator*)effect->AddComponent(new Animator(*effect, "animations/Effect/Beam/Beam", "Beam"));
		effect->SetPool(this);
		effect->SetAnimator(ani);
		effect->SetRigidBody(rig);
		effect->SetCollider(col);
		effect->AddTag("BeamEffect");
		effect->sortLayer = 5;
	};
	bombEffects.OnCreate = [this](BombEffect* effect)
	{
		BoxCollider* col = (BoxCollider*)effect->AddComponent(new BoxCollider(*effect));
		RigidBody2D* rig = (RigidBody2D*)effect->AddComponent(new RigidBody2D(*effect));
		col->SetRect({ 0.0f, 0.0f, 20.0f, 20.0f });
		col->SetOffset({ 24.0f, 24.0f });
		col->SetRigidbody(rig);
		col->SetTrigger(true);
		col->SetBounciness(0.2f);
		effect->SetPool(this);
		effect->SetCollider(col);
		Animator* ani = (Animator*)effect->AddComponent(new Animator(*effect, "animations/Effect/Bomb/Bomb", "Ready"));
		effect->AddTag("BombEffect");
		effect->SetAnimator(ani);
	};
	cutterEffects.Init(20);
	beamEffects.Init(100);
	bombEffects.Init(20);
}

void EffectPool::Release()
{
	GameObject::Release();
}

void EffectPool::Reset()
{
	GameObject::Reset();
}

void EffectPool::Update(float dt)
{
	GameObject::Update(dt);
}

void EffectPool::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}
