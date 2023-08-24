#pragma once
#include "SpriteGO.h"
#include "Animator.h"
#include "BoxCollider.h"
class EffectPool;
class BeamEffect : public SpriteGO
{
public:
	enum class Mode
	{
		Whip,
		Ball,
		Tornado,
		WindBall,
	};
protected:
	Mode mode = Mode::Whip;

	EffectPool* pool;
	BeamEffect* prevNode;
	Animator* animator;
	RigidBody2D* rigidbody;
	BoxCollider* collider;
	sf::Vector2f effectDirection;
	sf::Vector2f effectPoint;
	float effectRotation = -20.0f;
	float time = 0.0f;
	float removeTime = 0.0f;
public:
	BeamEffect(const std::string textureID = "sprites/effects/Beam_Effect.png", const std::string& name = "BeamEffect") 
		:SpriteGO(textureID, name) {};
	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(Collider* col) override;
	const float& GetTotalRotation() const;
	void Shot(const sf::Vector2f& power);
	void SetEffectDirection(const sf::Vector2f& effectDirection) { this->effectDirection = effectDirection; }
	void SetEffectRotation(const float& effectRotation) { this->effectRotation = effectRotation; }
	void SetTime(const float& time) { this->time = time; }
	void SetPrevNode(BeamEffect* prevNode) { this->prevNode = prevNode; }
	void SetPool(EffectPool* pool) { this->pool = pool; }
	void SetMode(const Mode& mode);
	void SetAnimator(Animator* animator) { this->animator = animator; }
	void SetRigidBody(RigidBody2D* rigidbody) { this->rigidbody = rigidbody; }
	void SetCollider(BoxCollider* collider) { this->collider = collider; }
	void Return();
};

