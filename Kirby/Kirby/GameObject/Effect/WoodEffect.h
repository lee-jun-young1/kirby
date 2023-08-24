#pragma once
#include "SpriteGO.h"
#include "Animator.h"
class EffectPool;

class WoodEffect : public SpriteGO
{
public:
	enum class EffectType
	{
		Apple,
		Breath
	};
protected:
	EffectPool* pool;
	Animator* animator;
	RigidBody2D* rigidbody;

	bool isBounced = false; 
	function<void(Collider*)> onTriggerEnter;

	float lifeTime = 5.0f;
public:
	WoodEffect(const std::string textureID = "sprites/effects/wood.png", const std::string& name = "WoodEffect")
		:SpriteGO(textureID, name) {};
	void SetPool(EffectPool* pool) { this->pool = pool; }
	void SetAnimator(Animator* animator) { this->animator = animator; }
	void SetRigidBody(RigidBody2D* rigidbody) { this->rigidbody = rigidbody; }
	void OnTriggerEnter(Collider* col);
	void AppleTriggerEnter(Collider* col);
	void SetType(EffectType type);
	virtual void Reset() override;
	virtual void Update(float dt) override;
	void Fire();
};

