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
	if (data["FlipX"].asBool())
	{
		SetFlipX(!flipX);
		SetOrigin({ (!flipX) ? groundSize.x : 0.f, 0.f });
	}
	
	inCameraEvent = [this]() {
		SetActive(true);
	};
	outCameraEvent = [this]() {
		SetActive(false);
	};

	switch (type)
	{
	case GroundType::Normal:
	{
		BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
		if (flipX)
		{
			boxCol->SetOffset({ data["OffSet"]["x"].asFloat() + groundSize.x, data["OffSet"]["y"].asFloat() });
		}
		else
		{
			boxCol->SetOffset({ data["OffSet"]["x"].asFloat(), data["OffSet"]["y"].asFloat() });
		}
	}
		break;
	case GroundType::Tilted:
	{
		BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
		boxCol->SetRect({ (float)rect.left - 2.0f, (float)rect.top, (float)rect.width + 4.0f, (float)rect.height });
		if (flipX)
		{
			boxCol->SetRotationOffset(data["Angle"].asFloat() * -1);
			boxCol->SetOffset({ data["OffSet"]["x"].asFloat() - groundSize.x, data["OffSet"]["y"].asFloat() });
		}
		else
		{
			boxCol->SetRotationOffset(data["Angle"].asFloat());
			boxCol->SetOffset({ data["OffSet"]["x"].asFloat(), data["OffSet"]["y"].asFloat()});
		}
	}
	break;
	case GroundType::Throught:
		break;
	case GroundType::Background:
		break;
	case GroundType::Crashed:
		break;
	case GroundType::Transpar:
		BoxCollider* boxCol = (BoxCollider*)AddComponent(new BoxCollider(*this));
		sprite.setColor(sf::Color::Transparent);
		break;
	}
}
