#include "stdafx.h"
#include "SpriteFont.h"
#include "rapidcsv.h"

SpriteFont::SpriteFont(std::string spriteFontDataPath)
{
	rapidcsv::Document doc(spriteFontDataPath);
	std::vector<char> ids = doc.GetColumn<char>(0);
	std::vector<std::string> values = doc.GetColumn<std::string>(1);
	std::vector<int> left = doc.GetColumn<int>(2);
	std::vector<int> top = doc.GetColumn<int>(3);
	std::vector<int> width = doc.GetColumn<int>(4);
	std::vector<int> height = doc.GetColumn<int>(5);

	for (int j = 0; j < ids.size(); j++)
	{
		std::cout << ids[j] << " ";
		spriteDataTable.insert({ ids[j], {values[j], {left[j], top[j], width[j], height[j]} } });
	}
}

const SpriteFontData& SpriteFont::Get(char key) const
{
	auto find = spriteDataTable.find(key);
	if (find == spriteDataTable.end())
	{
		std::cout << "Not Defined Key :: " << key << std::endl;
		return SpriteFontData();
	}
	return find->second;
}
