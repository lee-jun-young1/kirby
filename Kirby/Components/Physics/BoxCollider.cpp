#include "stdafx.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#ifdef _DEBUG
#include <Framework.h>
#endif

BoxCollider::BoxCollider(GameObject& gameObject)
	:Collider(gameObject, ColliderType::Box)
{
	rect = { gameObject.GetPosition().x, gameObject.GetPosition().y, gameObject.GetSize().x, gameObject.GetSize().y };
	offset = gameObject.GetOrigin() * -1.0f;
}

void BoxCollider::SetRect(sf::Rect<float> rect)
{
	this->rect = rect;
}

sf::Rect<float> BoxCollider::GetRect()
{
	return rect;
}

bool BoxCollider::CheckCross(Collider* col)
{
	if (!isEnable || !col->IsEnable())
	{
		return false;
	}
	switch (col->GetColliderType())
	{
	case ColliderType::Box:
	{
		return rect.intersects(((BoxCollider*)col)->GetRect());
	}
	case ColliderType::Circle:
	{
		//Âü°í : https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
		CircleCollider* circleCol = (CircleCollider*)col;
		sf::Vector2f circleCenter = circleCol->GetCenter();
		float radius = circleCol->GetRaidus();
		sf::Vector2f boxCenter = GetCenter();

		float xDistance = abs(circleCenter.x - boxCenter.x);
		float yDistance = abs(circleCenter.y - boxCenter.y);

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
	}
}

void BoxCollider::Init()
{
#ifdef _DEBUG
	debugShape.setFillColor(sf::Color::Transparent);
	debugShape.setOutlineColor(isTrigger ? sf::Color::Blue : sf::Color::Green);
	debugShape.setOutlineThickness(1.0f);
#endif
}

void BoxCollider::Update(float deltaTime)
{
	if (!isEnable)
	{
		return;
	}
	rect.left = gameObject.GetPosition().x + offset.x;
	rect.top = gameObject.GetPosition().y + offset.y;
	Collider::Update(deltaTime);
#ifdef _DEBUG
	debugShape.setPosition({ rect.left, rect.top });
	debugShape.setSize({ rect.width, rect.height });
#endif
}

void BoxCollider::Draw(sf::RenderWindow& window)
{
	Collider::Draw(window);
}

void BoxCollider::OnGUI(sf::RenderWindow& window)
{
#ifdef _DEBUG
	if (FRAMEWORK.IsDebugging(Framework::DebugMode::Collider) && IsEnable())
	{
		window.draw(debugShape);
	}
#endif
}

sf::Vector2f BoxCollider::GetCenter()
{
	return sf::Vector2f((rect.left + rect.width * 0.5f), (rect.top + rect.height * 0.5f));
}

float BoxCollider::GetWidth()
{
	return rect.width;
}

float BoxCollider::GetHeight()
{
	return rect.height;
}

#ifdef _DEBUG
void BoxCollider::OnCollisionEnter(Collider* col)
{
	Collider::OnCollisionEnter(col);
}

void BoxCollider::OnCollisionStay(Collider* col)
{
	Collider::OnCollisionStay(col);
	debugShape.setOutlineColor(sf::Color::Red);
}

void BoxCollider::OnCollisionExit(Collider* col)
{
	Collider::OnCollisionExit(col);
	debugShape.setOutlineColor(sf::Color::Green);
}

void BoxCollider::OnTriggerEnter(Collider* col)
{
	Collider::OnTriggerEnter(col);
}

void BoxCollider::OnTriggerStay(Collider* col)
{
	Collider::OnTriggerStay(col);
	debugShape.setOutlineColor(sf::Color::Red);
}

void BoxCollider::OnTriggerExit(Collider* col)
{
	Collider::OnTriggerExit(col);
	debugShape.setOutlineColor(sf::Color::Blue);
}
#endif