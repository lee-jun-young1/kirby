#pragma once
#include "Component.h"
#include <GameObject.h>
class RigidBody2D : public Component
{
protected:
	bool useGravity;
	bool isVerticalCollided;
	sf::Vector2f velocity;
public:
	virtual bool IsEnable();
	virtual void SetEnable(bool isEnable);
	RigidBody2D(GameObject& gameObject);
	// Component을(를) 통해 상속됨

	void SetGravity(bool useGravity);

	sf::Vector2f GetVelocity();
	void AddForce(sf::Vector2f velocity);
	void SetVelocity(sf::Vector2f velocity);

	virtual void Init() override;
	virtual void Reset() override { velocity = { 0.0f, 0.0f }; };
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Release() override;
	void OnCollisionEnter(Collider* thisCol, Collider* diffCol);
	void OnCollisionStay(Collider* thisCol, Collider* diffCol);
	void OnCollisionExit(sf::Vector2f normal);

	void OnTriggerEnter();
	void OnTriggerStay();
	void OnTriggerExit(sf::Vector2f normal);

	// Component을(를) 통해 상속됨
	virtual void OnGameObjectEnable() override;
	virtual void OnGameObjectDisable() override;
};