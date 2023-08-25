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
		cameraCenter = Utils::Lerp(view->getCenter(), { areaBounds.left + (areaBounds.width * 0.5f), areaBounds.top + (areaBounds.height * 0.5f) }, cameraTime);
		break;
	}
	view->setCenter(cameraCenter);
	cameraTime = 0.0f;

	//Check object
	for (auto go : *gameObjects)
	{
		if (go->GetName() == "GenPoint" || go->GetName() == "Mob" || go->GetName() == "Ground" || go->GetName() == "ThroughtableGround")
		{
			SetActiveInCamera((SpriteGO*)go);
		}
		//if (go->GetName() == "CameraArea")
		//{
		//	if (((CameraArea*)go)->GetGlobalBounds().contains(position))
		//	{
		//		SetCameraArea(((CameraArea*)go));
		//	}
		//	if (((CameraArea*)go)->GetType() == CameraType::Fixed && !((CameraArea*)go)->GetGlobalBounds().contains(position))
		//	{
		//		SetPrevCam();
		//	}
		//}
	}
}

void Camera::SetCameraArea(CameraArea* area)
{
	this->area = area;
	prevType = type;
	prevAreaBounds = areaBounds;
	type = area->GetType();
	areaBounds = area->GetGlobalBounds();
	checkArea = areaBounds;

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
}

void Camera::SetPrevCam()
{
	type = prevType;
	areaBounds = prevAreaBounds;
}

void Camera::SetActiveInCamera(GameObject* target)
{

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
