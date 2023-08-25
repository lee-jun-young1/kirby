#pragma once
#include "SpriteGO.h"
class ClearItem : public SpriteGO
{
public:
	ClearItem(const std::string textureID = "sprites/item/ClearStar.png", const std::string& name = "Item") :SpriteGO(textureID, name) {}

	//virtual void Init() override;
	virtual void Init() override;
	virtual void OnEnable() override;

	virtual void OnCollisionEnter(Collider* col) override;
};

