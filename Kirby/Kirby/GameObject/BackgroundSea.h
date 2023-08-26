#pragma once
#include "SpriteGO.h"
class BackgroundSea : public SpriteGO
{
protected:


public:
	BackgroundSea(const std::string textureID = "", const std::string& name = ""):SpriteGO(textureID, name){}

	virtual void Init() override;
	virtual void Reset() override;

};

