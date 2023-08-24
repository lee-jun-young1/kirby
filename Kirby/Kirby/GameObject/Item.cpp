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
		rect = { 120, 24, 24, 24 };
		break;
	case ItemType::Normal:
		rect = { 96, 24, 24, 24 };
		break;
	}
	sprite.setTextureRect(rect);
	SetSize({24.0f, 24.0f});
}

void Item::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Kirby")
	{
		std::cout << (int)itemType << std::endl;
		switch (itemType)
		{
		case ItemType::Life:
			break;
		case ItemType::God:
			break;
		case ItemType::MaxTomato:
			kirby->Heal(maxTomatoHealHp);
			break;
		case ItemType::Normal:
			kirby->Heal(normalHealHp);
			break;
		}
		SetActive(false);
	}
}
