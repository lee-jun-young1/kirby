#include "stdafx.h"
#include "CameraPointer.h"
#include "SceneManager.h"
#include "SceneExample.h"
void CameraPointer::Init()
{
	shape->setFillColor(sf::Color::Transparent);
}

void CameraPointer::Reset()
{
	SetActive(true);
}

const sf::Vector2f& CameraPointer::CalculateCameraPosition(const sf::Vector2f& rate)
{
	return sf::Vector2f(GetGlobalBounds().left + (GetGlobalBounds().width * rate.x), GetGlobalBounds().top + (GetGlobalBounds().height * rate.y));
}

void CameraPointer::OnTriggerEnter(Collider* col)
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
void CameraPointer::OnTriggerStay(Collider* col)
{
}
void CameraPointer::OnTriggerExit(Collider* col)
{
	//if (col->GetGameObject().GetName() != targetGO->GetName() || type != CameraType::Fixed)
	//{
	//	return;
	//}
	//SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	//scene->SetCameraType(prevType);
	//scene->SetCamera();
}