#include "stdafx.h"
#include "ResourceManager.h"
#include <rapidcsv.h>

ResourceManager::~ResourceManager()
{
	for (auto pair : mapTexture)
	{
		delete std::get<0>(pair.second);
	}
	mapTexture.clear();
	for (auto pair : mapFont)
	{
		delete std::get<0>(pair.second);
	}
	mapFont.clear();
	for (auto pair : mapSoundBuffer)
	{
		delete std::get<0>(pair.second);
	}
	mapSoundBuffer.clear();
	for (auto pair : mapAnimationClip)
	{
		delete std::get<0>(pair.second);
	}
	mapAnimationClip.clear();
	for (auto pair : mapSpriteFont)
	{
		delete std::get<0>(pair.second);
	}
	mapSpriteFont.clear();
}

void ResourceManager::Init()
{
	rapidcsv::Document doc("data/GlobalResources.csv");
	std::vector<int> types = doc.GetColumn<int>(0);
	std::vector<std::string> paths = doc.GetColumn<std::string>(1);
	std::cout << "===Global===" << std::endl;
	for (int i = 0; i < types.size(); ++i)
	{
		std::cout << types[i] << ", " << paths[i] << std::endl;
		Load((ResourceTypes)types[i], paths[i], true);
	}
	std::cout << "===Global===" << std::endl;
}

void ResourceManager::UnLoadAll()
{
	for (auto pair : mapTexture)
	{
		if (!std::get<0>(pair.second))
		{
			delete std::get<0>(pair.second);
		}
	}
	mapTexture.clear();
	for (auto pair : mapFont)
	{
		if (!std::get<0>(pair.second))
		{
			delete std::get<0>(pair.second);
		}
	}
	mapFont.clear();
	for (auto pair : mapSoundBuffer)
	{
		if (!std::get<0>(pair.second))
		{
			delete std::get<0>(pair.second);
		}
	}
	mapSoundBuffer.clear();
	for (auto pair : mapAnimationClip)
	{
		if (!std::get<0>(pair.second))
		{
			delete std::get<0>(pair.second);
		}
	}
	mapAnimationClip.clear();
	for (auto pair : mapSpriteFont)
	{
		if (!std::get<0>(pair.second))
		{
			delete std::get<0>(pair.second);
		}
	}
	mapSpriteFont.clear();
}

void ResourceManager::Load(ResourceTypes t, const std::string path, bool isStatic)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(path);
		if (mapTexture.end() == it)
		{
			auto texture = new sf::Texture();
			texture->loadFromFile(path);

			mapTexture.insert({ path, std::make_tuple(texture, isStatic) });
		}
	}
		break;

	case ResourceTypes::Font:
	{
		auto it = mapFont.find(path);
		if (mapFont.end() == it)
		{
			auto font = new sf::Font();
			font->loadFromFile(path);

			mapFont.insert({ path, std::make_tuple(font, isStatic) });
		}
	}
		break;

	case ResourceTypes::SoundBuffer:
	{
		auto it = mapSoundBuffer.find(path);
		if (mapSoundBuffer.end() == it)
		{
			auto soundBuffer = new sf::SoundBuffer();
			soundBuffer->loadFromFile(path);

			mapSoundBuffer.insert({ path, std::make_tuple(soundBuffer, isStatic) });
		}
	}
		break;
	case ResourceTypes::AnimationClip:
	{
		auto it = mapAnimationClip.find(path);
		if (mapAnimationClip.end() == it)
		{
			auto clip = new AnimationClip();
			clip->LoadFromFile(path);

			mapAnimationClip.insert({ path, std::make_tuple(clip, isStatic) });
		}
	}
		break;
	case ResourceTypes::SpriteFont:
	{
		auto it = mapSpriteFont.find(path);
		if (mapSpriteFont.end() == it)
		{
			auto sFont = new SpriteFont(path);

			mapSpriteFont.insert({ path, std::make_tuple(sFont, isStatic) });
		}
	}
	break;
	}
}

void ResourceManager::Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array, bool isStatic)
{
	for (const auto& tuple : array)
	{
		Load(std::get<0>(tuple), std::get<1>(tuple), isStatic);
	}
}

void ResourceManager::Unload(ResourceTypes t, const std::string path)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(path);
		if (it != mapTexture.end())
		{
			if (std::get<1>(it->second))
			{
				std::cout << "Cannot Remove Static Resource" << std::endl;
			}
			else
			{
				delete std::get<0>(it->second);
				mapTexture.erase(it);
			}
		}
	}
	break;

	case ResourceTypes::Font:
	{
		auto it = mapFont.find(path);
		if (it != mapFont.end())
		{
			if (std::get<1>(it->second))
			{
				std::cout << "Cannot Remove Static Resource" << std::endl;
			} 
			else
			{
				delete std::get<0>(it->second);
				mapFont.erase(it);
			}
		}
	}
	break;

	case ResourceTypes::SoundBuffer:
	{
		auto it = mapSoundBuffer.find(path);
		if (it != mapSoundBuffer.end())
		{
			if (std::get<1>(it->second))
			{
				std::cout << "Cannot Remove Static Resource" << std::endl;
			}
			else
			{
				delete std::get<0>(it->second);
				mapSoundBuffer.erase(it);
			}
		}
	}
	break;

	case ResourceTypes::AnimationClip:
	{
		auto it = mapAnimationClip.find(path);
		if (it != mapAnimationClip.end())
		{
			if (std::get<1>(it->second))
			{
				std::cout << "Cannot Remove Static Resource" << std::endl;
			}
			else
			{
				delete std::get<0>(it->second);
				mapAnimationClip.erase(it);
			}
		}
	}
	break;
	case ResourceTypes::SpriteFont:
	{
		auto it = mapSpriteFont.find(path);
		if (it != mapSpriteFont.end())
		{
			if (std::get<1>(it->second))
			{
				std::cout << "Cannot Remove Static Resource" << std::endl;
			}
			else
			{
				delete std::get<0>(it->second);
				mapSpriteFont.erase(it);
			}
		}
	}
	break;
	}
}

void ResourceManager::Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
{
	for (const auto& tuple : array)
	{
		Unload(std::get<0>(tuple), std::get<1>(tuple));
	}
}

sf::Texture* ResourceManager::GetTexture(const std::string& id)
{
	auto it = mapTexture.find(id);
	if (mapTexture.end() != it)
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

sf::Font* ResourceManager::GetFont(const std::string& id)
{
	auto it = mapFont.find(id);
	if (mapFont.end() != it)
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

sf::SoundBuffer* ResourceManager::GetSoundBuffer(const std::string& id)
{
	auto it = mapSoundBuffer.find(id);
	if (mapSoundBuffer.end() != it)
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

AnimationClip* ResourceManager::GetAnimationClip(const std::string& id)
{
	auto it = mapAnimationClip.find(id);
	if (mapAnimationClip.end() != it)
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

SpriteFont* ResourceManager::GetSpriteFont(const std::string& id)
{
	auto it = mapSpriteFont.find(id);
	if (mapSpriteFont.end() != it)
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}