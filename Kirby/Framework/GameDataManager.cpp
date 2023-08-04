#include "stdafx.h"
#include "GameDataManager.h"
#include "sstream"
#include <fstream>
#include <string>

GameDataManager::GameDataManager()
{
	Load();
}

GameDataManager::~GameDataManager()
{
	Save();
}

void GameDataManager::Load()
{
	std::ifstream file("data/PlayerPrefs.userdata");
	std::stringstream texts;

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			texts << line;
		}
		file.close();
	}
	std::cout << texts.str() << std::endl;

	std::string text = texts.str();
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(text, root);
	if (!parsingSuccessful)
	{
		std::cout << "Error parsing the string" << std::endl;
	}

	std::cout << "Load ::" << std::endl;
	for (Json::Value::const_iterator outer = root.begin(); outer != root.end(); outer++)
	{
		for (Json::Value::const_iterator inner = (*outer).begin(); inner != (*outer).end(); inner++)
		{
			if (outer.key() == "intTable")
			{
				data.intTable.insert({ inner.key().asString(), inner->asInt() });
			}
			else if (outer.key() == "floatTable")
			{
				data.floatTable.insert({ inner.key().asString(), inner->asFloat() });
			}
			else if (outer.key() == "stringTable")
			{
				data.stringTable.insert({ inner.key().asString(), inner->asString() });
			}
			std::cout << inner.key() << ": " << *inner << std::endl;
		}
	}
}

void GameDataManager::Save()
{
	Json::Value root;
	root["intTable"] = ConvertToJson(data.intTable);
	root["floatTable"] = ConvertToJson(data.floatTable);
	root["stringTable"] = ConvertToJson(data.stringTable);

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, root);
	std::cout << "Save ::" << std::endl;
	std::cout << json_file << std::endl;


	std::ofstream ofile("data/PlayerPrefs.userdata");

	if (ofile.is_open()) {
		ofile << json_file;
		ofile.close();
	}
}

Json::Value GameDataManager::ConvertToJson(std::unordered_map<std::string, int>& map)
{
	Json::Value json;

	for (auto& element : map)
	{
		json[element.first] = element.second;
	}
	return json;
}

Json::Value GameDataManager::ConvertToJson(std::unordered_map<std::string, float>& map)
{
	Json::Value json;

	for (auto& element : map)
	{
		json[element.first] = element.second;

	}
	return json;
}

Json::Value GameDataManager::ConvertToJson(std::unordered_map<std::string, std::string>& map)
{
	Json::Value json;

	for (auto& element : map)
	{
		json[element.first] = element.second;

	}
	return json;
}


void GameDataManager::DeleteAll()
{
	data.floatTable.clear();
	data.intTable.clear();
	data.stringTable.clear();
}

void GameDataManager::DeleteKey(const std::string& key)
{
	auto fit = data.floatTable.begin();
	for (fit; fit != data.floatTable.end(); fit++)
	{
		if (fit->first == key)
		{
			data.floatTable.erase(fit);
			break;
		}
	}
	auto iit = data.intTable.begin();
	for (iit; iit != data.intTable.end(); iit++)
	{
		if (iit->first == key)
		{
			data.intTable.erase(iit);
			break;
		}
	}
	auto sit = data.stringTable.begin();
	for (sit; sit != data.stringTable.end(); sit++)
	{
		if (sit->first == key)
		{
			data.stringTable.erase(sit);
			break;
		}
	}
}

const float& GameDataManager::GetFloat(const std::string& key, const float& defaultValue) const
{
	auto fit = data.floatTable.begin();
	for (fit; fit != data.floatTable.end(); fit++)
	{
		if (fit->first == key)
		{
			return fit->second;
		}
	}
	return defaultValue;
}

const int& GameDataManager::GetInt(const std::string& key, const int& defaultValue) const
{
	auto iit = data.intTable.begin();
	for (iit; iit != data.intTable.end(); iit++)
	{
		if (iit->first == key)
		{
			return iit->second;
		}
	}
	return defaultValue;
}

const std::string& GameDataManager::GetString(const std::string& key, const std::string& defaultValue) const
{
	auto sit = data.stringTable.begin();
	for (sit; sit != data.stringTable.end(); sit++)
	{
		if (sit->first == key)
		{
			return sit->second;
		}
	}
	return defaultValue;
}

const bool& GameDataManager::HasKey(const std::string& key) const
{
	auto fit = data.floatTable.begin();
	for (fit; fit != data.floatTable.end(); fit++)
	{
		if (fit->first == key)
		{
			return true;
		}
	}
	auto iit = data.intTable.begin();
	for (iit; iit != data.intTable.end(); iit++)
	{
		if (iit->first == key)
		{
			return true;
		}
	}
	auto sit = data.stringTable.begin();
	for (sit; sit != data.stringTable.end(); sit++)
	{
		if (sit->first == key)
		{
			return true;
		}
	}
	return false;
}

void GameDataManager::SetFloat(const std::string& key, const float& value)
{
	auto fit = data.floatTable.begin();
	for (fit; fit != data.floatTable.end(); fit++)
	{
		if (fit->first == key)
		{
			fit->second = value;
			return;
		}
	}

	data.floatTable.insert({ key, value });
}

void GameDataManager::SetInt(const std::string& key, const float& value)
{
	auto iit = data.intTable.begin();
	for (iit; iit != data.intTable.end(); iit++)
	{
		if (iit->first == key)
		{
			iit->second = value;
			return;
		}
	}

	data.intTable.insert({ key, value });
}

void GameDataManager::SetString(const std::string& key, const std::string& value)
{
	auto sit = data.stringTable.begin();
	for (sit; sit != data.stringTable.end(); sit++)
	{
		if (sit->first == key)
		{
			sit->second = value;
		}
	}

	data.stringTable.insert({ key, value });
}
