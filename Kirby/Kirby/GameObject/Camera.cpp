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
void Camera::Init()
{
	SetFillColor(sf::Color::Transparent);
}

void Camera::Reset()
{
	GameObject::Reset();
	physicsLayer = (int)PhysicsLayer::Ground;
	BoxCollider* camCol = (BoxCollider*)this->AddComponent(new BoxCollider(*this));
	camCol->SetTrigger(true);
	
	//realCheckArea = GetGlobalBounds();
	//realCheckArea.left -= correctSize.x;
	//realCheckArea.top -= correctSize.y;
	//realCheckArea.width += (correctSize.x * 2.f);
	//realCheckArea.height += (correctSize.y * 2.f);
}

void Camera::MoveCamera(float dt)
{
	cameraTime += dt * 2.5f;
	sf::Vector2f cameraCenter = kirby->GetPosition();
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

void Camera::SetActiveInCamera(GameObject* target)
{
	//커비를 기준으로
	realCheckArea = kirby->sprite.getGlobalBounds();
	realCheckArea.left -= correctSize.x;
	realCheckArea.top -= correctSize.y;
	realCheckArea.width += (correctSize.x * 2.f);
	realCheckArea.height += (correctSize.y * 2.f);

	if (realCheckArea.contains(target->GetPosition()))
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

void Camera::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().GetName() != "Kirby")
	{
		return;
	}
	SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	if (scene->GetCamera() != this)
	{
		scene->SetCamera(this);
	}
}

void Camera::OnTriggerStay(Collider* col)
{
	//SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	//if (scene->GetCamera() == this)
	//{
	//	if (kirby->GetPosition().x - cellSize.x * 0.5f <= GetGlobalBounds().left)
	//	{
	//		kirby->SetPosition(GetGlobalBounds().left + cellSize.x * 0.5f, kirby->GetPosition().y);
	//	}
	//	else if(kirby ->GetPosition().x + cellSize.x * 0.5f >= GetGlobalBounds().left + GetGlobalBounds().width)
	//	{
	//		kirby->SetPosition(GetGlobalBounds().left + GetGlobalBounds().width - cellSize.x * 0.5f, kirby->GetPosition().y);
	//	}
	//	if (kirby->GetPosition().y - cellSize.y <= GetGlobalBounds().top)
	//	{
	//		kirby->SetPosition(kirby->GetPosition().y, GetGlobalBounds().top + cellSize.y);
	//	}
	//}
}

void Camera::OnTriggerExit(Collider* col)
{

}
