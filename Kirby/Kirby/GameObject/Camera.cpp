#include "stdafx.h"
#include "Camera.h"
#include "SceneManager.h"
#include "SceneExample.h"
void Camera::Init()
{
	shape->setFillColor(sf::Color::Transparent);
}

void Camera::Reset()
{
	SetActive(true);
}

const sf::Vector2f& Camera::CalculateCameraPosition(const sf::Vector2f& rate)
{
	return sf::Vector2f(GetGlobalBounds().left + (GetGlobalBounds().width * rate.x), GetGlobalBounds().top + (GetGlobalBounds().height * rate.y));
}

void Camera::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().GetName() != targetGO->GetName())
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
}
void Camera::OnTriggerExit(Collider* col)
{
	//if (col->GetGameObject().GetName() != targetGO->GetName() || type != CameraType::Fixed)
	//{
	//	return;
	//}
	//SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	//scene->SetCameraType(prevType);
	//scene->SetCamera();
}