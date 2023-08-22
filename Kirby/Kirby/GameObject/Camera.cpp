#include "stdafx.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h";
#include "SceneExample.h"
#include "SpriteGO.h"
#include "Framework.h"
#include "Utils.h"
#include "BoxCollider.h"
void Camera::Init()
{
	SetFillColor(sf::Color::Transparent);
	//SetOutlineThickness(1.2f);
	//SetOutlineColor(sf::Color::Cyan);
}

void Camera::Reset()
{
	GameObject::Reset();
	size.x = data["EndPosition"]["x"].asFloat() - data["Position"]["x"].asFloat() + cellSize.x;
	size.y = data["EndPosition"]["y"].asFloat() - data["Position"]["y"].asFloat() + cellSize.y;
	SetSize(size);
	SetPosition({ data["Position"]["x"].asFloat(), data["Position"]["y"].asFloat() });
	physicsLayer = (int)PhysicsLayer::Ground;
	BoxCollider* camCol = (BoxCollider*)this->AddComponent(new BoxCollider(*this));
	camCol->SetTrigger(true);
}

void Camera::Update(float dt)
{
	//if (!isIn && !isStay)
	//{
	//	return;
	//}
}

void Camera::MoveCamera(float dt)
{
	cameraTime += dt * 2.5f;
	sf::Vector2f cameraCenter = player->GetPosition();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::FloatRect bounds = GetGlobalBounds();

	switch (type)
	{
	case CameraType::Free:
		if (cameraCenter.x <= bounds.left + windowSize.x * 0.5f)
		{
			cameraCenter.x = bounds.left + windowSize.x * 0.5f;
		}
		else if (cameraCenter.x >= bounds.left + bounds.width - windowSize.x * 0.5f)
		{
			cameraCenter.x = bounds.left + bounds.width - windowSize.x * 0.5f;
		}

		if (cameraCenter.y <= bounds.top + windowSize.y * 0.5f)
		{
			cameraCenter.y = bounds.top + windowSize.y * 0.5f;
		}
		else if (cameraCenter.y >= bounds.top + bounds.height - windowSize.y * 0.5f)
		{
			cameraCenter.y = bounds.top + bounds.height - windowSize.y * 0.5f;
		}
		break;
	case CameraType::Fixed:
		cameraCenter = Utils::Lerp(view->getCenter(), {bounds.left + (bounds.width * 0.5f), bounds.top + (bounds.height * 0.5f)}, cameraTime);
		break;
	}
	view->setCenter(cameraCenter);
	cameraTime = 0.0f;
}

void Camera::CheckObjectInCamera(SpriteGO* target)
{
	std::cout << target->GetName() << std::endl;
	if (GetGlobalBounds().contains(target->GetPosition()))
	{

	}
	else
	{

	}
}

void Camera::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().GetName() != player->GetName())
	{
		return;
	}
	SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	if (scene->GetCamera() == this)
	{
		//scene->SetCamera();
	}
	else
	{
		scene->SetCamera(this);
	}
}

void Camera::OnTriggerStay(Collider* col)
{
}

void Camera::OnTriggerExit(Collider* col)
{

}
