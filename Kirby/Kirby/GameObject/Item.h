#pragma once
#include "SpriteGO.h"
class Item : public SpriteGO
{
protected:
	ItemType itemType;

public:
	Item(const std::string textureID = "", const std::string& name = "");

	const ItemType& GetItemType() const { return itemType; }
	void SetItemType(const ItemType& type) { itemType = type; }
};

