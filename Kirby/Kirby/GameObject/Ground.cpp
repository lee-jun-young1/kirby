#include "stdafx.h"
#include "Ground.h"
#include "BoxCollider.h"
Ground::Ground(const std::string textureID, const std::string& name)
	:SpriteGO(textureID, name)
{
}
void Ground::Init()
{
	SpriteGO::Init();
}

void Ground::Reset()
{
	SpriteGO::Reset();
	AddTag("Ground");
	sprite.setTextureRect(textureRect);
	SetSize(groundSize);

	if (node["FlipX"].asBool())
	{
		SetFlipX(GetFlipX());
		SetOrigin({ (GetFlipX()) ? groundSize.x : 0.f, 0.f });
	}

	//physicsLayer = (int)PhysicsLayer::Ground;

	//switch (type)
	//{
	//case GroundType::Normal:
	//{
	//	BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
	//	boxCol->SetRect({ (float)textureRect.left, (float)textureRect.top, (float)textureRect.width, (float)textureRect.height });
	//	if (flipX)
	//	{
	//		boxCol->SetOffset({ node["OffSet"]["x"].asFloat(), node["OffSet"]["y"].asFloat() });
	//	}
	//	else
	//	{
	//		boxCol->SetOffset({ node["OffSet"]["x"].asFloat(), node["OffSet"]["y"].asFloat() });
	//	}
	//}
	//break;
	//case GroundType::Tilted:
	//{
	//	BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
	//	boxCol->SetRect({ (float)textureRect.left, (float)textureRect.top, (float)textureRect.width + 2.0f, (float)textureRect.height * 0.01f });
	//	if (flipX)
	//	{
	//		boxCol->SetRotationOffset(node["Angle"].asFloat() * -1);
	//		boxCol->SetOffset({ node["OffSet"]["x"].asFloat(), node["OffSet"]["y"].asFloat() - 1.0f });
	//	}
	//	else
	//	{
	//		boxCol->SetRotationOffset(node["Angle"].asFloat());
	//		boxCol->SetOffset({ node["OffSet"]["x"].asFloat(), node["OffSet"]["y"].asFloat() - 1.0f });
	//	}
	//}
	//break;
	//case GroundType::Throught:
	//	break;
	//case GroundType::Background:
	//	break;
	//case GroundType::Crashed:
	//{
	//	AddTag("Suctionable");
	//	BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
	//	boxCol->SetRect({ (float)textureRect.left, (float)textureRect.top, (float)textureRect.width, (float)textureRect.height });
	//}
	//break;
	//case GroundType::Transpar:
	//{
	//	BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
	//	boxCol->SetRect({ (float)textureRect.left, (float)textureRect.top, (float)textureRect.width, (float)textureRect.height });
	//	sprite.setColor(sf::Color::Transparent);
	//}
	//break;
	//}


	inCameraEvent = [this]() {
		SetActive(true);
	};
	outCameraEvent = [this]() {
		SetActive(false);
	};
}
