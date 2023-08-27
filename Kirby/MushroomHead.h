#pragma once
#include "SpriteGO.h"
class MushroomHead :
    public SpriteGO
{
public:
	MushroomHead(const std::string textureID = "", const std::string& name = "")
		:SpriteGO(textureID, name) {};
	virtual void OnCollisionEnter(Collider* col);
};

