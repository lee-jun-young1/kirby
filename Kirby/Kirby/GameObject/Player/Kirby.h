#pragma once
#include "Playable.h"
#include <Animator.h>
#include <BoxCollider.h>
#include <RigidBody2D.h>
#include <Suction.h>

enum class KirbyState
{
	Idle,
	Balloon,
	Eat,
	Falling,
	Jump,
	Collided,
	Tackle,
	Suction,
	Sit,
};


class Kirby : public Playable
{
protected:
	KirbyAbility ability;
	KirbyState state;
	vector<string> abilityTextureIDs;

    Animator* animator;
	BoxCollider* collider;
	RigidBody2D* rigidbody;
	float speed = 30.0f;

	Suction* suction;

	KirbyAbility keepInMouseAbility;

	SpriteGO* starEffect;

public:
	Kirby(const std::string textureID = "", const std::string& name = "") : Playable(textureID, name) {};
	virtual void MoveKey(const sf::Vector2f& axis, const float& deltaTime) override;
	virtual void DashKey(const sf::Vector2f& axis, const float& deltaTime) override;
	virtual void MoveKeyEnd() override;
	virtual void ChargeKey() override;
	virtual void ChargeKeyContinue() override;
	virtual void ChargeKeyEnd() override;
	virtual void SitKey() override;
	virtual void SitKeyEnd() override;
	virtual void JumpKey() override;

	void SetAbility();
	void SetSuction(Suction* suction) { this->suction = suction; }
	void SetStarEffect(SpriteGO* starEffect) { this->starEffect = starEffect; }

	void Eat();
	void Sit();

	void ShotStar();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void OnCollisionEnter(Collider* col) override;

	// Playable을(를) 통해 상속됨
	virtual void VKey() override;
};

