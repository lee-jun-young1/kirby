#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "RigidBody2D.h"
#include "Utils.h"

Collider::Collider(GameObject& gameObject, ColliderType type)
	:Component(gameObject, ComponentType::Collider, false), type(type), rigidbody(nullptr), isCollide(false), bounciness(0.0f), isTrigger(false)
{
	//Physics.AddColliders(this, gameObject.physicsLayer);
}

Collider::~Collider()
{
	Physics.RemoveColliders(this, gameObject.physicsLayer);
}

ColliderType Collider::GetColliderType()
{
	return type;
}

RigidBody2D* Collider::GetRigidBody()
{
	return rigidbody;
}

void Collider::SetRigidbody(RigidBody2D* rigidbody)
{
	this->rigidbody = rigidbody;
}

void Collider::SetBounciness(float bounciness)
{
	this->bounciness = bounciness;
}

sf::Vector2f Collider::GetCenter()
{
	return sf::Vector2f();
}

bool Collider::CheckCross(Collider* col)
{
	return false;
}

sf::Vector2f Collider::GetNormal(Collider* col)
{
	float rotation = GetRotationOffset() + GetGameObject().GetRotation();
	if (rotation == 0)
	{
		sf::Vector2f val = (col->GetCenter() - GetCenter());
		val.x /= GetWidth() + col->GetWidth();
		val.y /= GetHeight() + col->GetHeight();

		sf::Vector2f result;
		if (abs(val.x) >= abs(val.y))
		{
			//cout << " Y " << endl;
			result.x = val.x > 0.0f ? 1.0f : -1.0f;
		}
		else
		{
			//cout << " X " << endl;
			result.y = (val.y > 0.0f ? 1.0f : -1.0f);
		}

		return result;
	}
	else
	{
		sf::Vector2f result;

		sf::Vector2f rotatedVertex[4];

		rotatedVertex[0] = GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(GetWidth() * -0.5f, GetHeight() * -0.5f), rotation);
		rotatedVertex[1] = GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(GetWidth() * -0.5f, GetHeight() * 0.5f), rotation);
		rotatedVertex[2] = GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(GetWidth() * 0.5f, GetHeight() * -0.5f), rotation);
		rotatedVertex[3] = GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(GetWidth() * 0.5f, GetHeight() * 0.5f), rotation);


		sf::Vector2f top = rotatedVertex[0];
		sf::Vector2f bottom = rotatedVertex[0];
		sf::Vector2f left = rotatedVertex[0];
		sf::Vector2f right = rotatedVertex[0];
		for (int i = 1; i < 4; i++)
		{
			if (top.y > rotatedVertex[i].y)
			{
				top = rotatedVertex[i];
			}
			if (top.y < rotatedVertex[i].y)
			{
				bottom = rotatedVertex[i];
			}
			if (left.x > rotatedVertex[i].x)
			{
				left = rotatedVertex[i];
			}
			if (right.x < rotatedVertex[i].x)
			{
				right = rotatedVertex[i];
			}
		}


		if (col->GetCenter().y < left.y && col->GetCenter().x < top.x)
		{
			result.x = -1.0f;
		}
		else if (col->GetCenter().y < right.y && col->GetCenter().x > top.x)
		{
			result.y = -1.0f;
		}
		else if (col->GetCenter().y > left.y && col->GetCenter().x < bottom.x)
		{
			result.y = 1.0f;
		}
		else if (col->GetCenter().y > right.y && col->GetCenter().x > bottom.x)
		{
			result.x = 1.0f;
		} 
		result = Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), result, (int)rotation % 90);
		return result;
	}
}

void Collider::SetTrigger(bool isTrigger)
{
	this->isTrigger = isTrigger;
}

void Collider::SetOffset(sf::Vector2f offset)
{
	this->offset = offset;
}

void Collider::SetRotationOffset(const float& offset)
{
	rotationOffset = offset;
}

const float& Collider::GetRotationOffset()
{
	return rotationOffset;
}

sf::Vector2f Collider::GetOffset()
{
	return offset;
}

void Collider::OnCollisionEnter(Collider* col)
{
	if (!isTrigger && !col->isTrigger && rigidbody != nullptr)
	{
		sf::Vector2f normal = GetNormal(col);
		if (bounciness > 0.0f) 
		{
			sf::Vector2f newVelocity = rigidbody->GetVelocity();


			cout << normal.x << " " << normal.y << endl;

			if (abs(normal.x) > 0.0f)
			{
				newVelocity.x *= -1.0f;
			}
			else if (abs(normal.y) > 0.0f)
			{
				newVelocity.y *= -1.0f;
			}

			newVelocity *= bounciness;
			rigidbody->SetVelocity(newVelocity);
		}

		rigidbody->OnCollisionEnter(this, col);
	}
	gameObject.OnCollisionEnter(col);
}


void Collider::OnCollisionStay(Collider* col)
{
	if (!isTrigger && !col->isTrigger && rigidbody != nullptr)
	{
		rigidbody->OnCollisionStay(this, col);
	}
	gameObject.OnCollisionStay(col);
}

void Collider::OnCollisionExit(Collider* col)
{
	//sf::Vector2f thisVelocity = col->GetRigidBody()->GetVelocity();
	//sf::Vector2f colVelocity = col->GetRigidBody()->GetVelocity();

	if (rigidbody != nullptr)
	{
		sf::Vector2f normal = GetNormal(col);
		rigidbody->OnCollisionExit(normal);
	}
	//TODO if Not Trigger Stop In Here

	gameObject.OnCollisionExit(col);
}

void Collider::OnTriggerEnter(Collider* col)
{
	gameObject.OnTriggerEnter(col);
}

void Collider::OnTriggerStay(Collider* col)
{
	gameObject.OnTriggerStay(col);
}

void Collider::OnTriggerExit(Collider* col)
{
	if (rigidbody != nullptr)
	{
		sf::Vector2f normal = GetNormal(col);
		rigidbody->OnTriggerExit(normal);
	}
	gameObject.OnTriggerExit(col);
}

void Collider::Init()
{
}

void Collider::Reset()
{
	if (gameObject.IsActive() && isEnable)
	{
		Physics.AddColliders(this, gameObject.physicsLayer);
	}
}

void Collider::Update(float deltaTime)
{
	list<Collider*> currentColliders;
	CheckAllCollide(currentColliders);


	for (auto curIt = currentColliders.begin(); curIt != currentColliders.end(); curIt++)
	{
		bool isStay = false;
		if (curIt == currentColliders.end())
		{
			break;
		}
		if (!(*curIt)->IsEnable())
		{
			continue;
		}
		for (auto it = prevCollideList.begin(); it != prevCollideList.end(); it++)
		{
			if (it == prevCollideList.end())
			{
				break;
			}
			if (*curIt == *it)
			{
				isStay = true;
				if (isTrigger)
				{
					OnTriggerStay(*curIt);
				}
				else
				{
					OnCollisionStay(*curIt);
				}
				it = prevCollideList.erase(it);
				break;
			}
		}
		if(!isStay)
		{
			if (isTrigger) 
			{
				OnTriggerEnter(*curIt);
			}
			else
			{
				OnCollisionEnter(*curIt);
			}
		}
	}

	auto col = prevCollideList.begin();
	for (col; col != prevCollideList.end(); col++)
	{
		if (isTrigger)
		{
			OnTriggerExit(*col);
		}
		else
		{
			OnCollisionExit(*col);
		}
	}
	prevCollideList.clear();
	if (currentColliders.size() > 0)
	{
		prevCollideList = currentColliders;
	}
}

void Collider::Draw(sf::RenderWindow& window)
{
}

void Collider::Release()
{
}

bool Collider::CheckAllCollide(list<Collider*>& colliderList)
{
	auto colliders = Physics.GetColliders(gameObject.physicsLayer);
	if (colliders.size() < 0)
	{
		return false;
	}
	for (auto col : colliders)
	{
		if (col != this && CheckCross(col))
		{
			colliderList.push_back(col);
		}
	}

	return colliderList.size() > 0;
}

void Collider::SetEnable(bool isEnable)
{
	Component::SetEnable(isEnable);
	bool preEnable = this->isEnable;
	if (gameObject.IsActive() && preEnable != isEnable)
	{
		if (isEnable)
		{
			Physics.AddColliders(this, gameObject.physicsLayer);
		}
		else if(!isEnable)
		{
			Physics.RemoveColliders(this, gameObject.physicsLayer);
		}
	}
}

void Collider::OnGameObjectEnable()
{
	if (isEnable)
	{
		Physics.AddColliders(this, gameObject.physicsLayer);
	}
}

void Collider::OnGameObjectDisable()
{
	if (isEnable)
	{
		Physics.RemoveColliders(this, gameObject.physicsLayer);
	}
}
