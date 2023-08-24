#pragma once
#include "SpriteGO.h"
#include "Animator.h"
#include "Animation.h"
class Background : public SpriteGO
{
protected:
	StageIndex stageIndex;

public: 
	const StageIndex& GetStageIndex() const { return stageIndex; }
	
	virtual void Reset() override;
};

