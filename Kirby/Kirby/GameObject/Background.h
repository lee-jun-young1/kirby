#pragma once
#include "SpriteGO.h"
#include "Animation.h"
class Background : public SpriteGO
{
protected:
	StageIndex stageIndex = StageIndex::GreenGreen;

	std::vector<Animation*> animations;

public: 
	Background(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {}
	const StageIndex& GetStageIndex() const { return stageIndex; }
	
	virtual void Reset() override;
};

