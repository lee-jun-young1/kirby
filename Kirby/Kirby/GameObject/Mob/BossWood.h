#pragma once
#include "Mob.h"
#include <EffectPool.h>
#include <ClearItem.h>

class BossWood : public Mob
{
	enum class Pattern
	{
		Wait = -1,
		None,
		Apple,
		Breath,
		Death,
	};
	Animator* animator;
	EffectPool* effectPool;
	Pattern pattern = Pattern::Breath;
	int eventCount = 0;

	ClearItem* clearItem;

public:
	BossWood(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Boss_Wood.png", const string& name = "Mob")
		:Mob(type, textureID, name) {}

	void SetAnimator(Animator* animator) { this->animator = animator; }

	virtual void Damage(const int& damage, const float hitAxisX) override;

	virtual void Init() override;
	virtual void Reset() override;
	void WakeUp();
	virtual void Update(float dt) override;
	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;

	void SetEffectPool(EffectPool* effectPool) { this->effectPool = effectPool; }
};

