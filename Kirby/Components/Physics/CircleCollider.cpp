#include "stdafx.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Utils.h"


CircleCollider::CircleCollider(GameObject& gameObject)
	:Collider(gameObject, ColliderType::Circle)
{
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

void CircleCollider::Update(float deltaTime)
{
	if (!isEnable)
	{
		return;
	}
	center = gameObject.GetPosition() + offset;
	Collider::Update(deltaTime);
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
