#pragma once
#include "SpriteGO.h"
#include "Animation.h"
class Background : public SpriteGO
{
protected:
	StageIndex stageIndex = StageIndex::GreenGreen;
	std::vector<Animation*> animations;

	sf::Vector2f repeatPosition;

public: 
	Background(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {}
	const StageIndex& GetStageIndex() const { return stageIndex; }
	
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

