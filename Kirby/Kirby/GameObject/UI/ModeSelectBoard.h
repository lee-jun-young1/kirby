#pragma once
#include "SpriteGO.h"
class ModeButton;
class ModeSelectBoard : public SpriteGO
{
protected:
	sf::RectangleShape outLine;

	bool isTwinkle = false;
	float twinkleTimer = 0.0f;
	float twinkleInterval = 0.2f;

	std::vector<ModeButton*> modes;
	int currentModeIndex = 0;
public:
	ModeSelectBoard(const std::string textureID, const std::string& name) : SpriteGO(textureID, name) {}

	void AddMode(ModeButton* mode) { modes.push_back(mode); }
	void RefreshOutLine();

	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

