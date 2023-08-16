#include "stdafx.h"
#include "CameraPointer.h"
#include "SceneManager.h"
#include "SceneExample.h"
void CameraPointer::Init()
{
	//shape->setFillColor(sf::Color::Transparent);
	//shape->setOutlineColor(sf::Color::Cyan);
	//shape->setOutlineThickness(0.2f);
	//sortLayer = 10;
}

void CameraPointer::Reset()
{
	SetActive(true);
}

void CameraPointer::Update(float dt)
{

}

void CameraPointer::OnTriggerEnter(Collider* col)
{
	isCollide = false;
}
void CameraPointer::OnTriggerStay(Collider* col)
{
	if ((int)col->GetCenter().x == (int)GetPosition().x)
	{

	}
}
void CameraPointer::OnTriggerExit(Collider* col)
{
	SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	std::cout << (int)scene->GetCameraType() << std::endl;
	if (scene->GetCameraType() == type)
	{
		scene->SetCameraType(scene->GetPrevCameraType());
	}
	else
	{
		scene->SetPrevCameraType(scene->GetCameraType());
		scene->SetCameraType(type);
	}
}