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
	for (int i = 0; i < 4; i++)
	{
		debugShape[i].setFillColor(sf::Color::Cyan);
		debugShape[i].setRadius(3.0f);
	}
	debugShape2.setFillColor(sf::Color::Cyan);
	debugShape2.setRadius(3.0f);
}

void RigidBody2D::Update(float deltaTime)
{
	sf::Vector2f position = gameObject.GetPosition();
	if (useGravity && !isVerticalCollided)
	{
		velocity += sf::Vector2f(0.0f, mass * FRAMEWORK.GetGravity() * FRAMEWORK.GetDPM() * deltaTime);
	}
	position += velocity * deltaTime;
	gameObject.SetPosition(position);
	isVerticalCollided = false;
}

void RigidBody2D::OnGUI(sf::RenderWindow& window)
{
#ifdef _DEBUG
	if (FRAMEWORK.IsDebugging(Framework::DebugMode::Collider) && IsEnable())
	{
		for (int i = 0; i < 4; i++)
		{
			window.draw(debugShape[i]);
		}
		window.draw(debugShape2);
	}
#endif
}

void RigidBody2D::Release()
{
}

void RigidBody2D::OnCollisionEnter(Collider* thisCol, Collider* diffCol)
{
	//sf::Rect<float> border = sf::Rect<float>(gameObject.GetPosition().x + GetWidth() * 0.5f, gameObject.GetPosition().y + GetHeight() * 0.5f,
	//	(GetWidth() + col->GetWidth()) * 0.5f, (GetHeight() + col->GetHeight()) * 0.5f);

	sf::Vector2f normal = thisCol->GetNormal(diffCol);
}

void RigidBody2D::OnCollisionStay(Collider* thisCol, Collider* diffCol, const float& deltaTime)
{
	if (diffCol->IsTrigger())
	{
		isVerticalCollided = false;
		return;
	}

	float rotation = diffCol->GetRotationOffset() + diffCol->GetGameObject().GetRotation();
	bool inversed = ((int)rotation / 180) % 2 == 1;

	sf::Vector2f normal = diffCol->GetNormal(thisCol);

	velocity = velocity * (1.0f - drag * deltaTime);

	if (rotation == 0)
	{
		if (normal.x > 0.0f && velocity.x <= 0.0f)
		{
			velocity.x = 0.0f;
			gameObject.SetPosition(diffCol->GetCenter().x + (diffCol->GetWidth() * 0.5f) - 0.001f - thisCol->GetOffset().x, gameObject.GetPosition().y);
		}
		else if (normal.x < 0.0f && velocity.x >= 0.0f)
		{
			velocity.x = 0.0f;
			gameObject.SetPosition(diffCol->GetCenter().x - (diffCol->GetWidth() * 0.5f) - thisCol->GetWidth() + 0.001f - thisCol->GetOffset().x, gameObject.GetPosition().y);
		}
		else if (normal.y >= 0.0f && velocity.y < 0.0f)
		{
			isVerticalCollided = true;
			velocity.y = 0.0f;
			//cout << (normal.y > 0.0f ? rect.top + rect.height : rect.top - rect.height) << endl;
			gameObject.SetPosition(gameObject.GetPosition().x, diffCol->GetCenter().y + (diffCol->GetHeight()) - 0.001f - thisCol->GetOffset().y);
		}
		else if (normal.y <= 0.0f && velocity.y >= 0.0f)
		{
			isVerticalCollided = true;
			velocity.y = 0.0f;
			//cout << (normal.y > 0.0f ? rect.top + rect.height : rect.top - rect.height) << endl;
			gameObject.SetPosition(gameObject.GetPosition().x, diffCol->GetCenter().y - (diffCol->GetHeight() * 0.5f) - thisCol->GetHeight() + 0.001f - thisCol->GetOffset().y);
		}
	}
	else
	{
		float xPos = gameObject.GetPosition().x;
		sf::Vector2f rotatedVertex[4];

		rotatedVertex[0] = diffCol->GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(diffCol->GetWidth() * -0.5f, diffCol->GetHeight() * -0.5f), rotation);
		rotatedVertex[1] = diffCol->GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(diffCol->GetWidth() * -0.5f, diffCol->GetHeight() * 0.5f), rotation);
		rotatedVertex[2] = diffCol->GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(diffCol->GetWidth() * 0.5f, diffCol->GetHeight() * -0.5f), rotation);
		rotatedVertex[3] = diffCol->GetCenter() + Utils::RotateWithPivot(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(diffCol->GetWidth() * 0.5f, diffCol->GetHeight() * 0.5f), rotation);

		for (int i = 0; i < 4; i++)
		{
			debugShape[i].setPosition(rotatedVertex[i]);
		}

		if (normal.y <= 0.0f && velocity.y >= 0.0f)
		{
			sf::Vector2f top = rotatedVertex[0];
			sf::Vector2f left = rotatedVertex[0];
			sf::Vector2f right = rotatedVertex[0];
			for (int i = 1; i < 4; i++)
			{
				if (top.y > rotatedVertex[i].y)
				{
					top = rotatedVertex[i];
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

			sf::Vector2f interPos;

			float centerX = thisCol->GetCenter().x;
			if (normal.x > 0.0f && thisCol->GetCenter().x < right.x)
			{
				isVerticalCollided = true;
				velocity.y = 0.0f;

				float t = (top.x - centerX) / (top.x - right.x);
				interPos = Utils::Lerp(top, right, t);
				debugShape2.setPosition(interPos.x, interPos.y);
				//gameObject.SetPosition(gameObject.GetPosition().x, interPos.y - (thisCol->GetHeight() - thisCol->GetGameObject().GetOrigin().y ));
				gameObject.SetPosition(gameObject.GetPosition().x, interPos.y);
			}
			else if (normal.x < 0.0f && thisCol->GetCenter().x > left.x)
			{
				isVerticalCollided = true;
				velocity.y = 0.0f;

				float t = (left.x - thisCol->GetCenter().x) / (left.x - top.x);
				interPos = Utils::Lerp(left, top, t);
				debugShape2.setPosition(interPos.x, interPos.y);
				//gameObject.SetPosition(gameObject.GetPosition().x, interPos.y + (thisCol->GetHeight() - thisCol->GetGameObject().GetOrigin().y ));
				gameObject.SetPosition(gameObject.GetPosition().x, interPos.y);
			}
			else
			{
				isVerticalCollided = false;
			}
		}
		else if (normal.y > 0.0f && velocity.y <= 0.0f)
		{
			velocity.y = 0.0f;


			sf::Vector2f bottom = rotatedVertex[0];
			sf::Vector2f left = rotatedVertex[0];
			sf::Vector2f right = rotatedVertex[0];
			for (int i = 1; i < 4; i++)
			{
				if (bottom.y < rotatedVertex[i].y)
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

			sf::Vector2f interPos;

			if (normal.x > 0.0f && thisCol->GetCenter().x < right.x)
			{
				float t = (bottom.x - thisCol->GetCenter().x) / (bottom.x - right.x);
				interPos = Utils::Lerp(bottom, right, t);
				debugShape2.setPosition(interPos.x, interPos.y);
				gameObject.SetPosition(gameObject.GetPosition().x, interPos.y + thisCol->GetGameObject().GetOrigin().y * 0.5f + thisCol->GetHeight());
			}
			else if (normal.x < 0.0f && thisCol->GetCenter().x > left.x)
			{
				float t = (left.x - thisCol->GetCenter().x) / (left.x - bottom.x);
				interPos = Utils::Lerp(left, bottom, t);
				debugShape2.setPosition(interPos.x, interPos.y);
				gameObject.SetPosition(gameObject.GetPosition().x, interPos.y + thisCol->GetGameObject().GetOrigin().y * 0.5f + thisCol->GetHeight());
			}
		}
	}
}

void RigidBody2D::OnCollisionExit(sf::Vector2f normal)
{
	//if (normal.y != 0.0f)
	{
		//velocity.x = 0.0f;
		isVerticalCollided = false;
	}
}

void RigidBody2D::OnTriggerEnter(Collider* thisCol, Collider* diffCol)
{
}

void RigidBody2D::OnTriggerStay(Collider* thisCol, Collider* diffCol)
{
	isVerticalCollided = false;
}

void RigidBody2D::OnTriggerExit(sf::Vector2f normal)
{
	//if (normal.y != 0.0f)
	{
		//velocity.x = 0.0f;
		isVerticalCollided = false;
	}
}

void RigidBody2D::OnGameObjectEnable()
{
}

void RigidBody2D::OnGameObjectDisable()
{
}
