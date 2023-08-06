#include "stdafx.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Utils.h"
#include <Framework.h>


CircleCollider::CircleCollider(GameObject& gameObject)
	:Collider(gameObject, ColliderType::Circle)
{
	center = { gameObject.GetPosition().x, gameObject.GetPosition().y };
	SetRadius(max(gameObject.GetSize().x, gameObject.GetSize().y) * 0.5f);
	offset = gameObject.GetOrigin() * -1.0f;
}

sf::Vector2f CircleCollider::GetCenter()
{
	return center;
}


void CircleCollider::SetRadius(const float& radius)
{
	this->radius = radius;
}

float CircleCollider::GetRaidus()
{
	return radius;
}

void CircleCollider::Init()
{
#ifdef _DEBUG
	debugShape.setFillColor(sf::Color::Transparent);
	debugShape.setOutlineColor(isTrigger ? sf::Color::Blue : sf::Color::Green);
	debugShape.setOutlineThickness(1.0f);
#endif
}

void CircleCollider::Update(float deltaTime)
{
	if (!isEnable)
	{
		return;
	}
	center = gameObject.GetPosition() + offset;
	Collider::Update(deltaTime);
#ifdef _DEBUG
	debugShape.setPosition(center);
	debugShape.setRadius(radius);
#endif
}

void CircleCollider::Draw(sf::RenderWindow& window)
{
	Collider::Draw(window);
}

void CircleCollider::OnGUI(sf::RenderWindow& window)
{
#ifdef _DEBUG
	if (FRAMEWORK.IsDebugging(Framework::DebugMode::Collider) && IsEnable())
	{
		window.draw(debugShape);
	}
#endif
}


bool CircleCollider::CheckCross(Collider* col)
{
	switch (col->GetColliderType())
	{
	case ColliderType::Box:
	{
		//Âü°í : https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
		sf::Rect<float> rect = ((BoxCollider*)col)->GetRect();

		sf::Vector2f boxCenter = col->GetCenter();

		float xDistance = abs(center.x - boxCenter.x);
		float yDistance = abs(center.y - boxCenter.y);

		//³ì»ö¿µ¿ª
		if (xDistance > (rect.width * 0.5f + radius)) { return false; }
		if (yDistance > (rect.height * 0.5f + radius)) { return false; }

		//Çª¸¥»ö¿µ¿ª
		if (xDistance <= (rect.width * 0.5f)) { return true; }
		if (yDistance <= (rect.height * 0.5f)) { return true; }

		//»¡°£¿µ¿ª
		float cornerDistance = (xDistance - rect.width * 0.5f) * (xDistance - rect.width * 0.5f)
			+ (yDistance - rect.height * 0.5f) * (yDistance - rect.height * 0.5f);
		return (cornerDistance <= (radius * radius));
	}
	case ColliderType::Circle:
	{
		return Utils::Distance(center, ((CircleCollider*)col)->center) <= radius + ((CircleCollider*)col)->radius;
	}
	}
}

float CircleCollider::GetWidth()
{
	return radius * 2.0f;
}

float CircleCollider::GetHeight()
{
	return radius * 2.0f;
}

#ifdef _DEBUG
void CircleCollider::OnCollisionEnter(Collider* col)
{
	Collider::OnCollisionEnter(col);
}

void CircleCollider::OnCollisionStay(Collider* col)
{
	Collider::OnCollisionStay(col);
	debugShape.setOutlineColor(sf::Color::Red);
}

void CircleCollider::OnCollisionExit(Collider* col)
{
	Collider::OnCollisionExit(col);
	debugShape.setOutlineColor(sf::Color::Green);
}

void CircleCollider::OnTriggerEnter(Collider* col)
{
	Collider::OnTriggerEnter(col);
}

void CircleCollider::OnTriggerStay(Collider* col)
{
	Collider::OnTriggerStay(col);
	debugShape.setOutlineColor(sf::Color::Red);
}

void CircleCollider::OnTriggerExit(Collider* col)
{
	Collider::OnTriggerExit(col);
	debugShape.setOutlineColor(sf::Color::Blue);
}
#endif