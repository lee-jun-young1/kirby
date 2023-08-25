#include "stdafx.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h";
#include "SceneExample.h"
#include "SpriteGO.h"
#include "Framework.h"
#include "Utils.h"
#include "BoxCollider.h"
#include "Kirby.h"
#include "CameraArea.h"

void Camera::Reset()
{
	GameObject::Reset();
	cameraCheck = true;
}

void Camera::Update(float deltaTime)
{
	cameraTime += deltaTime * 2.5f;
	sf::Vector2f cameraCenter = kirby->GetPosition();
	SetPosition(cameraCenter);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

	switch (type)
	{
	case CameraType::Free:
		if (cameraCenter.x <= areaBounds.left + windowSize.x * 0.5f)
		{
			cameraCenter.x = areaBounds.left + windowSize.x * 0.5f;
		}
		else if (cameraCenter.x >= areaBounds.left + areaBounds.width - windowSize.x * 0.5f)
		{
			cameraCenter.x = areaBounds.left + areaBounds.width - windowSize.x * 0.5f;
		}

		if (cameraCenter.y <= areaBounds.top + windowSize.y * 0.5f)
		{
			cameraCenter.y = areaBounds.top + windowSize.y * 0.5f;
		}
		else if (cameraCenter.y >= areaBounds.top + areaBounds.height - windowSize.y * 0.5f)
		{
			cameraCenter.y = areaBounds.top + areaBounds.height - windowSize.y * 0.5f;
		}
		break;
	case CameraType::Fixed:
	{
		cameraCenter = Utils::Lerp(view->getCenter(), { areaBounds.left + (areaBounds.width * 0.5f), areaBounds.top + (areaBounds.height * 0.5f) }, cameraTime);
		if (kirby->GetPosition().x <= areaBounds.left)
		{
			kirby->SetPosition(areaBounds.left, kirby->GetPosition().y);
		}
		else if (kirby->GetPosition().x + 12.0f >= areaBounds.left + areaBounds.width)
		{
			kirby->SetPosition(areaBounds.left + areaBounds.width - 12.0f, kirby->GetPosition().y);
		}

		if (kirby->GetPosition().y - 24.0f <= areaBounds.top)
		{
			kirby->SetPosition(kirby->GetPosition().x, areaBounds.top + 24.0f);
		}
	}
		break;
	}
	view->setCenter(cameraCenter);
	cameraTime = 0.0f;

	//Check object
	if (cameraCheck)
	{
		for (auto go : *gameObjects)
		{
			if (go->GetName() == "GenPoint" || go->GetName() == "Mob" || go->GetName() == "Ground" || go->GetName() == "ThroughtableGround")
			{
				SetActiveInCamera((SpriteGO*)go);
			}
		}
	}
}

void Camera::SetCameraArea(CameraArea* area)
{
	this->area = area;
	prevType = type;
	prevAreaBounds = areaBounds;
	type = area->GetType();
	areaBounds = area->GetGlobalBounds();
}

void Camera::SetType(const CameraType& type, const sf::Vector2f& position)
{
	prevType = this->type;
	this->type = type;
	if (type == CameraType::Fixed)
	{
		sf::Vector2f size = FRAMEWORK.GetWindowSize();
		areaBounds = {position.x - size.x * 0.5f, position.y - size.y * 0.5f, size.x, size.y};
		SetPosition(position);
	}
}

void Camera::DeActiveCurrentArea()
{
	SetPrevCam();
	area->SetActive(false);
	area = nullptr;
}

void Camera::DeActiveOtherAreas()
{
	std::list<GameObject*> list;
	SCENE_MANAGER.GetCurrentScene()->FindGameObjects(list, "CameraArea");
	for (auto go : list)
	{
		if (go == area)
		{
			continue;
		}
		go->SetActive(false);
	}
	cameraCheck = false;
}

void Camera::SetPrevCam()
{
	type = prevType;
	areaBounds = prevAreaBounds;
}

void Camera::SetActiveInCamera(GameObject* target)
{
	checkArea = kirby->sprite.getGlobalBounds();
	checkArea.left -= correctSize.x;
	checkArea.top -= correctSize.y;
	checkArea.width += correctSize.x * 2.0f;
	checkArea.height += correctSize.y * 2.0f;
	
	if (checkArea.contains(target->GetPosition()))
	{
		if (target->inCameraEvent != nullptr && !target->inCamera)
		{
			target->inCameraEvent();
			target->inCamera = true;
		}
	}
	else
	{
		if (target->outCameraEvent != nullptr)
		{
			target->outCameraEvent();
		}
		if (target->inCamera)
		{
			target->inCamera = false;
		}
	}
}
