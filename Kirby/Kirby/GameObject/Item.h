#pragma once
#include "SpriteGO.h"
class Item : public SpriteGO
{
protected:
	ItemType itemType;

public:
	const ItemType& GetItemType() const { return itemType; }
};

