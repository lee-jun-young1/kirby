#pragma once
#include "Component.h"
#include <GameObject.h>
class RigidBody2D : public Component
{
protected:
	bool useGravity;
	bool isVerticalCollided;
	sf::Vector2f velocity;
	float mass = 1.0f;
	float drag = 0.0f;

	sf::CircleShape debugShape[4];
	sf::CircleShape debugShape2;
public:
	virtual bool IsEnable();
	virtual void SetEnable(bool isEnable);
	RigidBody2D(GameObject& gameObject);
	// Component을(를) 통해 상속됨

	void SetGravity(bool useGravity);

	const bool& GetGravity();

	sf::Vector2f GetVelocity();
	void AddForce(sf::Vector2f velocity);
	void SetVelocity(sf::Vector2f velocity);

	const float& GetDrag() { return drag; } const
	void SetDrag(const float& drag) { this->drag = drag; }

	const float& GetMass() { return mass; } const
	void SetMass(const float& mass) { this->mass = mass; }

	virtual void Init() override;
	virtual void Reset() override { velocity = { 0.0f, 0.0f }; };
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override {};
	virtual void OnGUI(sf::RenderWindow& window) override;
	virtual void Release() override;
	void OnCollisionEnter(Collider* thisCol, Collider* diffCol);
	void OnCollisionStay(Collider* thisCol, Collider* diffCol, const float& deltaTime);
	void OnCollisionExit(sf::Vector2f normal);

	void OnTriggerEnter(Collider* thisCol, Collider* diffCol);
	void OnTriggerStay(Collider* thisCol, Collider* diffCol);
	void OnTriggerExit(sf::Vector2f normal);

	// Component을(를) 통해 상속됨
	virtual void OnGameObjectEnable() override;
	virtual void OnGameObjectDisable() override;
};