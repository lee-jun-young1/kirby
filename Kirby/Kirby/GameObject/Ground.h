#pragma once
#include "SpriteGO.h"
class Ground : public SpriteGO
{
protected:
	GroundType type = GroundType::None;
	int groundIndex;
	
	bool throughAble;
	bool crashAble;
public:
	Ground(const std::string textureID = "", const std::string& name = "");

	const int& GetGroundIndex() const { return groundIndex; }
	void SetGroundIndex(const int& index) { groundIndex = index; }

	const GroundType& GetGroundType() const { return type; }
	void SetGroundType(const GroundType& type) { this->type = type; }
};