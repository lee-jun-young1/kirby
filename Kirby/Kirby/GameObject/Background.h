#pragma once
#include "SpriteGO.h"
class Background : public SpriteGO
{
protected:
	StageIndex stageIndex;

public: 
	const StageIndex& GetStageIndex() const { return stageIndex; }
};

