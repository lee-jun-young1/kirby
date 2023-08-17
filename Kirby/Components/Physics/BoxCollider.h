#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
protected:
	sf::Rect<float> rect;
public:
	BoxCollider(GameObject& gameObject);

	void SetRect(sf::Rect<float> rect);
	sf::Rect<float> GetRect();

	virtual bool CheckCross(Collider* col) override;

	virtual void Init() override;
	//virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void OnGUI(sf::RenderWindow& window) override;

	// Collider을(를) 통해 상속됨
	virtual sf::Vector2f GetCenter() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;

	bool SATTest(const sf::Vector2f& axis, const sf::Vector2f& aLeftTop, const sf::Vector2f& aCenter, const sf::Vector2f& bLeftTop, const sf::Vector2f& bCenter, const sf::Vector2f& bRight, const sf::Vector2f& bTop);

	sf::Vector2f GetProjection(const sf::Vector2f& axis, const sf::Vector2f& target);

#ifdef _DEBUG
protected:
	sf::RectangleShape debugShape;
public:
	virtual void OnCollisionEnter(Collider* col) override;
	virtual void OnCollisionStay(Collider* col, const float& deltaTime) override;
	virtual void OnCollisionExit(Collider* col) override;

	virtual void OnTriggerEnter(Collider* col) override;
	virtual void OnTriggerStay(Collider* col) override;
	virtual void OnTriggerExit(Collider* col) override;
#endif
};

