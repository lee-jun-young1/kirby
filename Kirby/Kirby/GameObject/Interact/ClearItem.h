#pragma once
#include "SpriteGO.h"
class Kirby;
class ClearItem : public SpriteGO
{
protected:
	Kirby* kirby;

	int normalHealHp = 20;
	int maxTomatoHealHp = 100;
public:
	ClearItem(const std::string textureID = "sprites/item/items.png", const std::string& name = "Item") :SpriteGO(textureID, name) {}

	//virtual void Init() override;
	virtual void Reset() override;

	void SetKirby(Kirby* kirby) { this->kirby = kirby; }

	virtual void OnCollisionEnter(Collider* col) override;
};

