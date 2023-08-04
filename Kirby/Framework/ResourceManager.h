#pragma once
#include "Singleton.h"
#include <AnimationClip.h>
#include <SpriteFont.h>
class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
protected:
	ResourceManager() = default;
	virtual ~ResourceManager() override;

	std::map<std::string, std::tuple<sf::Texture*, bool>> mapTexture;
	std::map<std::string, std::tuple<sf::Font*, bool>> mapFont;
	std::map<std::string, std::tuple<sf::SoundBuffer*, bool>> mapSoundBuffer;
	std::map<std::string, std::tuple<AnimationClip*, bool>> mapAnimationClip;
	std::map<std::string, std::tuple<SpriteFont*, bool>> mapSpriteFont;
public:
	void Init();

	void UnLoadAll();

	void Load(ResourceTypes t, const std::string path, bool isStatic = false);
	void Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array, bool isStatic = false);

	void Unload(ResourceTypes t, const std::string path);
	void Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array);

	sf::Texture* GetTexture(const std::string& id);
	sf::Font* GetFont(const std::string& id);
	sf::SoundBuffer* GetSoundBuffer(const std::string& id);
	AnimationClip* GetAnimationClip(const std::string& id);
	SpriteFont* GetSpriteFont(const std::string& id);
};

#define Resources (ResourceManager::GetInstance())