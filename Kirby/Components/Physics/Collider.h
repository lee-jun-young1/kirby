#pragma once
#include "Component.h"
class RigidBody2D;

class Collider : public Component
{
protected:
	RigidBody2D* rigidbody;
	ColliderType type;
	float bounciness;
	std::list<Collider*> prevCollideList;
	bool isCollide;

	bool isTrigger;

	sf::Vector2f offset;
	float rotationOffset;

	virtual void OnCollisionEnter(Collider* col);
	virtual void OnCollisionStay(Collider* col);
	virtual void OnCollisionExit(Collider* col);

	virtual void OnTriggerEnter(Collider* col);
	virtual void OnTriggerStay(Collider* col);
	virtual void OnTriggerExit(Collider* col);
public:
	Collider(GameObject& gameObject, ColliderType type);
	virtual ~Collider();

	ColliderType GetColliderType();

	RigidBody2D* GetRigidBody();
	void SetRigidbody(RigidBody2D* rigidbody);
	void SetBounciness(float bounciness);

	virtual sf::Vector2f GetNormal(Collider* col);
	virtual bool CheckCross(Collider* col) = 0;
	virtual sf::Vector2f GetCenter() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

	void SetTrigger(bool isTrigger);

	void SetOffset(sf::Vector2f offset);
	sf::Vector2f GetOffset();

	void SetRotationOffset(const float& offset);
	const float& GetRotationOffset();


	bool CheckAllCollide(std::list<Collider*>& colliderList);

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Release() override;

	virtual void SetEnable(bool isEnable) override;
	virtual void OnGameObjectEnable() override;
	virtual void OnGameObjectDisable() override;
};