#include "stdafx.h"
#include "CameraArea.h"
#include "Camera.h"
void CameraArea::Reset()
{
	RectangleShapeGO::Reset();
	shape->setFillColor(sf::Color::Transparent);
	SetActive(true);
}

void CameraArea::OnTriggerEnter(Collider* col)
{
	if (camera == nullptr || col->GetGameObject().GetName() != "Camera")
	{
		return;
	}
	camera->SetCameraArea(this);
}

void CameraArea::OnTriggerExit(Collider* col)
{
	if (camera == nullptr || col->GetGameObject().GetName() != "Camera")
	{
		return;
	}
	//if (camera->GetType() == CameraType::Fixed)
	//{
	//	camera->SetPrevCam();
	//}
}
