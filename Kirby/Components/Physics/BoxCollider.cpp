#include "stdafx.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Utils.h"
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
		if (gameObject.GetRotation() == 0.0f && rotationOffset == 0.0f && 
			col->GetGameObject().GetRotation() == 0.0f && col->GetRotationOffset() == 0.0f)
		{
			return rect.intersects(((BoxCollider*)col)->GetRect());
		}

		//Distance > Diagonal Length
		if (Utils::Distance(GetCenter(), col->GetCenter()) > (GetWidth() * GetHeight() * 0.25f) + (col->GetWidth() * col->GetHeight() * 0.25f))
		{
			return false;
		}

		sf::Vector2f thisColRight = { 1.0f, 0.0f };
		thisColRight = Utils::RotateWithPivot({ 0.0f, 0.0f }, thisColRight, rotationOffset + gameObject.GetRotation());
		sf::Vector2f thisColTop = { 0.0f, 1.0f };
		thisColTop = Utils::RotateWithPivot({ 0.0f, 0.0f }, thisColTop, rotationOffset + gameObject.GetRotation());

		sf::Vector2f thisColLT = { rect.left, rect.top };
		thisColLT = Utils::RotateWithPivot(GetCenter(), thisColLT, rotationOffset + gameObject.GetRotation());

		sf::Vector2f collideColRight = { 1.0f, 0.0f };
		collideColRight = Utils::RotateWithPivot({ 0.0f, 0.0f }, collideColRight, col->GetRotationOffset() + col->GetGameObject().GetRotation());
		sf::Vector2f collideColTop = { 0.0f, 1.0f };
		collideColTop = Utils::RotateWithPivot({ 0.0f, 0.0f }, collideColTop, col->GetRotationOffset() + col->GetGameObject().GetRotation());

		sf::Vector2f collideColLT = { col->GetCenter().x - col->GetWidth() * 0.5f, col->GetCenter().y - col->GetHeight() * 0.5f };
		collideColLT = Utils::RotateWithPivot(col->GetCenter(), collideColLT, col->GetRotationOffset() + col->GetGameObject().GetRotation());

		bool testResult1 = SATTest(thisColRight, thisColLT, GetCenter(), collideColLT, col->GetCenter(), collideColRight, collideColTop);
		bool testResult2 = SATTest(thisColTop, thisColLT, GetCenter(), collideColLT, col->GetCenter(), collideColRight, collideColTop);
		bool testResult3 = SATTest(collideColRight, collideColLT, col->GetCenter(), thisColLT, GetCenter(), thisColRight, thisColTop);
		bool testResult4 = SATTest(collideColTop, collideColLT, col->GetCenter(), thisColLT, GetCenter(), thisColRight, thisColTop);

		return testResult1 && testResult2 && testResult3 && testResult4;
	}
	case ColliderType::Circle:
	{
		//Âü°í : https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
		CircleCollider* circleCol = (CircleCollider*)col;
		sf::Vector2f circleCenter = circleCol->GetCenter();
		float radius = circleCol->GetRaidus();
		sf::Vector2f boxCenter = GetCenter();

		if (gameObject.GetRotation() != 0.0f || rotationOffset != 0.0f)
		{
			circleCenter = Utils::RotateWithPivot(boxCenter, circleCenter, -(gameObject.GetRotation() + rotationOffset));
		}


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
	//debugShape.setPosition({ rect.left - offset.x, rect.top - offset.y });
	debugShape.setPosition({ (rect.left + rect.width) - offset.x, (rect.top + rect.height) - offset.y });
	debugShape.setSize({ rect.width, rect.height });
	debugShape.setRotation(rotationOffset + gameObject.GetRotation());
	debugShape.setOrigin(gameObject.GetOrigin());
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

bool BoxCollider::SATTest(const sf::Vector2f& axis, const sf::Vector2f& aLeftTop, const sf::Vector2f& aCenter,
	const sf::Vector2f& bLeftTop, const sf::Vector2f& bCenter, const sf::Vector2f& bRight, const sf::Vector2f& bUp)
{
	//3
	float aLength = Utils::Distance({0.0f, 0.0f}, GetProjection(axis, aCenter - aLeftTop));

	//5
	float bUpProjectionLength = Utils::Distance({ 0.0f, 0.0f }, GetProjection(bUp, bCenter - bLeftTop));
	sf::Vector2f bTopPosition = bUp * bUpProjectionLength;
	//6
	float b1Length = Utils::Distance({ 0.0f, 0.0f }, GetProjection(axis, bTopPosition));

	//7
	float bRightProjectionLength = Utils::Distance({ 0.0f, 0.0f }, GetProjection(bRight, bCenter - bLeftTop));
	sf::Vector2f bRightPosition = bRight * bRightProjectionLength;

	float b2Length = Utils::Distance({ 0.0f, 0.0f }, GetProjection(axis, bRightPosition));

	//8
	float targetLength = Utils::Distance({ 0.0f, 0.0f }, GetProjection(axis, aCenter - bCenter));


	return (aLength + b1Length + b2Length) > targetLength;
}

sf::Vector2f BoxCollider::GetProjection(const sf::Vector2f& axis, const sf::Vector2f& target)
{
	return (axis.x * target.x + axis.y * target.y) * axis;
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