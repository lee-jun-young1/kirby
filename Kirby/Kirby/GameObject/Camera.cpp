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
	SetOutlineThickness(0.2f);
	SetOutlineColor(sf::Color::Cyan);
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
	//if (!isIn && !isStay && this->GetGlobalBounds().contains(target->GetPosition()))
	//{
	//	std::cout << "Camera ON" << std::endl;
	//	isIn = true;
	//	isOut = false;
	//}

	//if (isIn && !this->GetGlobalBounds().contains(target->GetPosition()))
	//{
	//	std::cout << "Camera OFF" << std::endl;
	//	isOut = true;
	//	isIn = false;
	//	isStay = false;
	//}

	//if (isIn && !isOut && !isStay)
	//{
	//	isStay = true;
	//}

	if (!isIn && !isStay)
	{
		return;
	}

	cameraTime += dt * 2.5f;
	cameraCenter = target->GetPosition();
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
		cameraCenter = Utils::Lerp(view->getCenter(), { (bounds.left + bounds.width) * 0.5f, (bounds.top + bounds.height) * 0.5f }, cameraTime);
		break;
	}
	view->setCenter(cameraCenter);
	cameraTime = 0.0f;
}

void Camera::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().GetName() != target->GetName())
	{
		return;
	}
	SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	if (scene->GetCamera() == this)
	{
		scene->SetCamera();
	}
	else
	{
		scene->SetCamera(this);
	}
}

void Camera::OnTriggerStay(Collider* col)
{
	isStay = true;
}

void Camera::OnTriggerExit(Collider* col)
{

}
