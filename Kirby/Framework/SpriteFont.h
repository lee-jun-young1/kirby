#pragma once
#include "stdafx.h"

struct SpriteFontData
{
	std::string spriteID;
	sf::Rect<int> rect;
};

class SpriteFont
{
protected:
	std::unordered_map<char, SpriteFontData> spriteDataTable;
public:
	SpriteFont(std::string spriteFontDataPath);
	const SpriteFontData& Get(char key) const;
};

