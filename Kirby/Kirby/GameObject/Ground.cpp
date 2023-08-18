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
	sf::Vector2f position = { data["Position"]["x"].asFloat(), data["Position"]["y"].asFloat() };
	sf::IntRect rect = { data["TexturePosition"]["x"].asInt(), data["TexturePosition"]["y"].asInt(), (int)groundSize.x, (int)groundSize.y };
	AddTag("Ground");
	sprite.setTextureRect(rect);
	SetSize(groundSize);
	physicsLayer = (int)PhysicsLayer::Ground;
	sortLayer = data["SortLayer"].asInt();
	SetPosition(position);

	switch (type)
	{
	case GroundType::Normal:
		AddComponent(new BoxCollider(*this));
		break;
	case GroundType::Tilted:
	{
		BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
		boxCol->SetRotationOffset(data["Angle"].asFloat() + 90.f);
		boxCol->SetOffset({ data["OffSet"]["x"].asFloat(), data["OffSet"]["y"].asFloat() });
	}
	break;
	case GroundType::Throught:
		break;
	case GroundType::Background:
		break;
	case GroundType::Crashed:
		break;
	}
}
