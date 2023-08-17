#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class ShapeGameObj: public GameObject
{
protected:
	sf::Shape* shape;
	ShapeType type;
public:
	ShapeGameObj(ShapeType shapeType, const string& name = "");

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetOrigin(const Origins& origin) override;
	virtual void SetOrigin(const sf::Vector2f& origin) override;
	virtual void SetPosition(const sf::Vector2f& position) override;
	void SetFillColor(sf::Color color);
	void SetOutlineColor(sf::Color color);
	void SetOutlineThickness(const float& thickness);

	const sf::Color& GetFillColor() const;
	const sf::FloatRect& GetGlobalBounds() const;

	// GameObject을(를) 통해 상속됨
	virtual void Reset() override;

};

