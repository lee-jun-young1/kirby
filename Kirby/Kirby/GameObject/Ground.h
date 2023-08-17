#pragma once
#include "SpriteGO.h"
class Ground : public SpriteGO
{
protected:
	int groundIndex;
	bool throughAble;
public:
	Ground(const std::string textureID = "", const std::string& name = "");

	const int& GetGroundIndex() const { return groundIndex; }
	void SetGroundIndex(const int& index) { groundIndex = index; }

};