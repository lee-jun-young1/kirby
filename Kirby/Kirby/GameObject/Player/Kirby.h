#pragma once
#include "Playable.h"
#include <Animator.h>
#include <BoxCollider.h>
#include <RigidBody2D.h>
class Kirby : public Playable
{
protected:
    Animator* animator;
	BoxCollider* collider;
	RigidBody2D* rigidbody;
	float speed = 30.0f;
public:
	Kirby(const std::string textureID = "", const std::string& name = "") : Playable(textureID, name) {};
	virtual void Move(const sf::Vector2f& axis, const float& deltaTime) override;
	virtual void Dash(const sf::Vector2f& axis, const float& deltaTime) override;
	virtual void MoveEnd() override;
	virtual void Charge() override;
	virtual void ChargeEnd() override;
	virtual void Sit() override;
	virtual void SitEnd() override;
	virtual void Jump() override;


	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void OnCollisionEnter(Collider* col) override;
};

