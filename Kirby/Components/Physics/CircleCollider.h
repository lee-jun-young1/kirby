#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
protected:
	sf::Vector2f center;
	float radius;
public:
	CircleCollider(GameObject& gameObject);

	void SetRadius(const float& radius);
	float GetRaidus();

	virtual void Init() override;
	//virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void OnGUI(sf::RenderWindow& window) override;

	virtual bool CheckCross(Collider* col) override;

	// Collider을(를) 통해 상속됨
	virtual sf::Vector2f GetCenter() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;

#ifdef _DEBUG
protected:
	sf::CircleShape debugShape;
public:
	virtual void OnCollisionEnter(Collider* col) override;
	virtual void OnCollisionStay(Collider* col, const float& deltaTime) override;
	virtual void OnCollisionExit(Collider* col) override;

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
#endif
};

