#pragma once
#include "UIButton.h"
#include "json.h"
class MapToolPalette : public UIButton
{
protected:
	std::string name;
	sf::Vector2f endPosition;

public:
	MapToolPalette(const std::string textureID = "", const std::string& name = "") : UIButton(textureID, name) {}
	virtual ~MapToolPalette() override {};

	
	Json::Value additionalData;
};

