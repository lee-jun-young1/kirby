#pragma once
#include "Mob.h"
#include <EffectPool.h>

class BossWood : public Mob
{
	enum class Pattern
	{
		None,
		Apple,
		Breath,
		Death,
	};
	Animator* animator;
	EffectPool* effectPool;
	Pattern pattern = Pattern::Breath;
	int eventCount = 0;


public:
	BossWood(KirbyAbility type = KirbyAbility::None, const std::string textureID = "sprites/mob/Boss_Wood.png", const string& name = "BossWood")
		:Mob(type, textureID, name) {}
	void SetAnimator(Animator* animator) { this->animator = animator; }

	virtual void Damage(const int& damage, const float hitAxisX) override;

	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;

	void SetEffectPool(EffectPool* effectPool) { this->effectPool = effectPool; }
};

