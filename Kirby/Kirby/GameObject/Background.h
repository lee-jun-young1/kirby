#pragma once
#include "SpriteGO.h"
#include "Animation.h"

class Background : public SpriteGO
{
protected:
	StageIndex stageIndex = StageIndex::GreenGreen;
	std::vector<SpriteGO*> animations;
public: 
	const StageIndex& GetStageIndex() const { return stageIndex; }
	Background(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {}
	
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetAnimation(SpriteGO* go) { animations.push_back(go); };
};

