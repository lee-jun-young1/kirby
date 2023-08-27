#include "stdafx.h"
#include "Ground.h"
#include "BoxCollider.h"
Ground::Ground(const std::string textureID, const std::string& name)
	:SpriteGO(textureID, name)
{
}

void Ground::Reset()
{
	SpriteGO::Reset();
	AddTag("Ground");
	//sprite.setTextureRect(textureRect);
	SetSize(groundSize);
	physicsLayer = (int)PhysicsLayer::Ground;
	if (data["FlipX"].asBool())
	{
		SetFlipX(false);
		SetOrigin({ (!GetFlipX()) ? groundSize.x : 0.f, 0.f });
	}

	inCameraEvent = [this]() {
		SetActive(true);
	};
	outCameraEvent = [this]() {
		SetActive(false);
	};
}
