#pragma once
#include "SpriteGO.h"
class Kirby;
class Item : public SpriteGO
{
protected:
	ItemType itemType;
public:
	Item(const std::string textureID = "", const std::string& name = "") :SpriteGO(textureID, name) {}

	//virtual void Init() override;
	virtual void Reset() override;

	const ItemType& GetItemType() const { return itemType; }
	void SetItemType(const ItemType& type) { itemType = type; }

	virtual void OnCollisionEnter(Collider* col) override;
};

