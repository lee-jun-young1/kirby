#include "stdafx.h"
#include "CameraPointer.h"
#include "SceneManager.h"
#include "SceneExample.h"
void CameraPointer::Init()
{
	shape->setFillColor(sf::Color::Transparent);
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
	SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	prevType = scene->GetCameraType();
	scene->SetCameraType(type);
}
void CameraPointer::OnTriggerStay(Collider* col)
{
}
void CameraPointer::OnTriggerExit(Collider* col)
{
	SceneExample* scene = (SceneExample*)SCENE_MANAGER.GetCurrentScene();
	scene->SetCameraType(prevType);
}