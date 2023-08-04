#pragma once
#include "SpriteGO.h"
class Ground : public SpriteGO
{
protected:
	int groundIndex;
	bool throughAble;
public:
	const int& GetGroundIndex() const { return groundIndex; }
};