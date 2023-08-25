#pragma once
#include "SpriteGO.h"
class Kirby;
class Item : public SpriteGO
{
protected:
	ItemType itemType;
	Kirby* kirby;

	int normalHealHp = 20;
	int maxTomatoHealHp = 100;
public:
	Item(const std::string textureID = "sprites/item/items.png", const std::string& name = "Item") :SpriteGO(textureID, name) {}

	//virtual void Init() override;
	virtual void Reset() override;

	const ItemType& GetItemType() const { return itemType; }
	void SetItemType(const ItemType& type) { this->itemType = type; }
	void SetKirby(Kirby* kirby) { this->kirby = kirby; }

	virtual void OnCollisionEnter(Collider* col) override;
};

