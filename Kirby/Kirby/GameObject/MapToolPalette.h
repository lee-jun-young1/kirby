#pragma once
#include "UIButton.h"
#include "json.h"
class MapToolPalette : public UIButton
{
protected:
	Category category = Category::None;

	std::string name;
	sf::Vector2f endPosition;

public:
	MapToolPalette(const std::string textureID = "", const std::string& name = "") : UIButton(textureID, name) {}
	virtual ~MapToolPalette() override {};

	Category GetCategory() { return category; }
	void SetCategory(const Category& category) { this->category = category; }
	
	Json::Value additionalData;
};

