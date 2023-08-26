#pragma once
#include "SpriteGO.h"
class SpringBreezeKirby : public SpriteGO
{
protected:
	std::vector<GameObject*> targets;
	int currentTargetIndex = 0;
public:
	SpringBreezeKirby(const std::string textureID = "sprites/UI/SpringBreeze/SpringBreezeKirby.png", const std::string& name = "SpringBreezeKirby") :SpriteGO(textureID, name) {}

	void AddTarget(GameObject* target) { targets.push_back(target); }

	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
};

