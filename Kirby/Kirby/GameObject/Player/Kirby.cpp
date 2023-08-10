#include "stdafx.h"
#include "Kirby.h"

void Kirby::Move(const sf::Vector2f& axis, const float& deltaTime)
{
	SetPosition(GetPosition() + axis * speed * deltaTime);
}

void Kirby::Dash(const sf::Vector2f& axis, const float& deltaTime)
{
	SetPosition(GetPosition() + axis * speed * 2.0f * deltaTime);
}

void Kirby::Charge()
{
	cout << "Charge!!" << endl;
}

void Kirby::ChargeEnd()
{
	cout << "Charge end!!" << endl;
}

void Kirby::Init()
{
	//Kirby::animator = AddComponent(new Animator(*this, "", "Init"));
}
