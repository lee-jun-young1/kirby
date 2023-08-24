#include "stdafx.h"
#include "Item.h"
#include "Kirby.h"
void Item::Reset()
{
	SpriteGO::Reset();
	sf::IntRect rect;
	switch (itemType)
	{
	case ItemType::Life:
		rect = { 216, 0, 24, 24 };
		break;
	case ItemType::God:
		rect = { 216, 24, 24, 24 };
		break;
	case ItemType::MaxTomato:
		rect = { 96, 24, 24, 24 };
		break;
	case ItemType::Normal:
		rect = { 120, 24, 24, 24 };
		break;
	}
	sprite.setTextureRect(rect);
	SetSize({24.0f, 24.0f});
}

void Item::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Kirby")
	{
		switch (itemType)
		{
		case ItemType::Life:
			break;
		case ItemType::God:
			break;
		case ItemType::MaxTomato:
			break;
		case ItemType::Normal:
			break;
		}
		SetActive(false);
	}
}
