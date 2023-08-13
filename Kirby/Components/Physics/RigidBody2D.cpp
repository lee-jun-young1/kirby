#include "stdafx.h"
#include "RigidBody2D.h"
#include "Framework.h"
#include "Utils.h"

bool RigidBody2D::IsEnable()
{
	return true;
}

void RigidBody2D::SetEnable(bool isEnable)
{
	std::cout << "Rigidbody can not disable" << std::endl;
}

RigidBody2D::RigidBody2D(GameObject& gameObject)
	:useGravity(true), Component(gameObject, ComponentType::RigidBody, true), isVerticalCollided(false)
{
}

void RigidBody2D::SetGravity(bool useGravity)
{
	this->useGravity = useGravity;
}

sf::Vector2f RigidBody2D::GetVelocity()
{
	return velocity;
}

void RigidBody2D::AddForce(sf::Vector2f velocity)
{
	this->velocity += velocity;
}

void RigidBody2D::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void RigidBody2D::Init()
{
}

void RigidBody2D::Update(float deltaTime)
{
	sf::Vector2f position = gameObject.GetPosition();
	if (useGravity && !isVerticalCollided)
	{
		velocity += sf::Vector2f(0.0f, FRAMEWORK.GetGravity() * FRAMEWORK.GetDPM() * deltaTime);
	}
	position += velocity * deltaTime;
	gameObject.SetPosition(position);
}

void RigidBody2D::Draw(sf::RenderWindow& window)
{
}

void RigidBody2D::Release()
{
}

/// <summary>
/// 충돌진입시 처리
/// 주의 : left top이 아닙니다. 파라미터를 잘 살펴봐주세요.
/// </summary>
/// <param name="rect">
/// left = center.x
/// top = center.y
/// width, height = col1.size + col2.size
/// </param>
void RigidBody2D::OnCollisionEnter(Collider* thisCol, Collider* diffCol)
{
	//sf::Rect<float> border = sf::Rect<float>(gameObject.GetPosition().x + GetWidth() * 0.5f, gameObject.GetPosition().y + GetHeight() * 0.5f,
	//	(GetWidth() + col->GetWidth()) * 0.5f, (GetHeight() + col->GetHeight()) * 0.5f);

	sf::Vector2f normal = thisCol->GetNormal(diffCol);
}

void RigidBody2D::OnCollisionStay(Collider* thisCol, Collider* diffCol)
{

	float rotation = diffCol->GetRotationOffset() + diffCol->GetGameObject().GetRotation();
	bool inversed = ((int)rotation / 180) % 2 == 1;

	sf::Vector2f normal = diffCol->GetNormal(thisCol);

	if (normal.x > 0.0f)
	{
		velocity.x = 0.0f;
		gameObject.SetPosition(diffCol->GetCenter().x + (diffCol->GetWidth() * 0.5f) - 0.001f - thisCol->GetOffset().x, gameObject.GetPosition().y);
	}
	else if (normal.x < 0.0f)
	{
		velocity.x = 0.0f;
		gameObject.SetPosition(diffCol->GetCenter().x - (diffCol->GetWidth() * 0.5f) - thisCol->GetWidth() + 0.001f - thisCol->GetOffset().x, gameObject.GetPosition().y);
	}
	else if (normal.y > 0.0f && velocity.y < 0.0f)
	{
		isVerticalCollided = true;
		velocity.y = 0.0f;
		//cout << (normal.y > 0.0f ? rect.top + rect.height : rect.top - rect.height) << endl;
		gameObject.SetPosition(gameObject.GetPosition().x, diffCol->GetCenter().y + (diffCol->GetHeight()) - 0.001f - thisCol->GetOffset().y);
	}
	else if (normal.y < 0.0f && velocity.y > 0.0f)
	{
		isVerticalCollided = true;
		velocity.y = 0.0f;
		//cout << (normal.y > 0.0f ? rect.top + rect.height : rect.top - rect.height) << endl;
		gameObject.SetPosition(gameObject.GetPosition().x, diffCol->GetCenter().y - (diffCol->GetHeight() * 0.5f) - thisCol->GetHeight() + 0.001f - thisCol->GetOffset().y);
	}
}

void RigidBody2D::OnCollisionExit(sf::Vector2f normal)
{
	//if (normal.y != 0.0f)
	{
		velocity.x = 0.0f;
		isVerticalCollided = false;
	}
}

void RigidBody2D::OnTriggerEnter()
{
}

void RigidBody2D::OnTriggerStay()
{
}

void RigidBody2D::OnTriggerExit(sf::Vector2f normal)
{
	//if (normal.y != 0.0f)
	{
		velocity.x = 0.0f;
		isVerticalCollided = false;
	}
}

void RigidBody2D::OnGameObjectEnable()
{
}

void RigidBody2D::OnGameObjectDisable()
{
}
