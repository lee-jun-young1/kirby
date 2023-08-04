#pragma once
#include "Singleton.h"
#include <json.h>

struct Data
{
	std::unordered_map<std::string, int> intTable;
	std::unordered_map<std::string, float> floatTable;
	std::unordered_map<std::string, std::string> stringTable;
};

class GameDataManager : public Singleton<GameDataManager>
{
	friend Singleton<GameDataManager>;
protected:
	Data data;

	GameDataManager();
	virtual ~GameDataManager();


	Json::Value ConvertToJson(std::unordered_map<std::string, int>& map);
	Json::Value ConvertToJson(std::unordered_map<std::string, float>& map);
	Json::Value ConvertToJson(std::unordered_map<std::string, std::string>& map);
	void ConvertFromJson(std::unordered_map<std::string, int>& map, Json::Value::const_iterator outer);
	void ConvertFromJson(std::unordered_map<std::string, float>& map, Json::Value::const_iterator outer);
	void ConvertFromJson(std::unordered_map<std::string, std::string>& map, Json::Value::const_iterator outer);
public:
	void Load();
	void DeleteAll();
	void DeleteKey(const std::string& key);
	const float& GetFloat(const std::string& key, const float& defaultValue = 0.0f) const;
	const int& GetInt(const std::string& key, const int& defaultValue = 0) const;
	const std::string& GetString(const std::string& key, const std::string& defaultValue = "") const;
	const bool& HasKey(const std::string& key) const;
	void Save();
	void SetFloat(const std::string& key, const float& value);
	void SetInt(const std::string& key, const float& value);
	void SetString(const std::string& key, const std::string& value);
};

#define PlayerPrefs (GameDataManager::GetInstance())