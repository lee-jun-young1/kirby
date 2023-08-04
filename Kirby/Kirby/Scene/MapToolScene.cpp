#include "stdafx.h"
#include "MapToolScene.h"
#include "GameObject.h"
#include "json.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "Door.h"
#include "Ground.h"
#include "AmbientObject.h"
#include "Framework.h"
#include <fstream>

void MapToolScene::SaveData()
{
	Json::Value rootNode;

	rootNode["Stage"] = (int)stageIndex;

	for (auto go : gameObjects)
	{
		if (go->GetName() == "Player")
		{
			Json::Value node;
			node["PositionX"] = ((Player*)go)->GetPosition().x;
			node["PositionY"] = ((Player*)go)->GetPosition().y;
			rootNode[go->GetName()] = node;
		}
		else if (go->GetName() == "Item")
		{
			Json::Value node;
			node["Type"] = (int)((Item*)go)->GetItemType();
			node["PositionX"] = ((Item*)go)->GetPosition().x;
			node["PositionY"] = ((Item*)go)->GetPosition().y;
			rootNode[go->GetName()] = node;
		}
		else if (go->GetName() == "Enemy")
		{
			Json::Value node;
			node["Type"] = (int)((Enemy*)go)->GetEnemyType();
			node["PositionX"] = ((Enemy*)go)->GetPosition().x;
			node["PositionY"] = ((Enemy*)go)->GetPosition().y;
			rootNode[go->GetName()] = node;
		}
		else if (go->GetName() == "Door")
		{
			Json::Value node;
			node["PositionX"] = ((Door*)go)->GetPosition().x;
			node["PositionY"] = ((Door*)go)->GetPosition().y;
			node["MovePositionX"] = ((Door*)go)->GetMovePosition().x;
			node["MovePositionY"] = ((Door*)go)->GetMovePosition().y;
			rootNode[go->GetName()] = node;
		}
		else if (go->GetName() == "Ground")
		{
			Json::Value node;
			node["GroundIndex"] = ((Ground*)go)->GetGroundIndex();
			node["PositionX"] = ((Ground*)go)->GetPosition().x;
			node["PositionY"] = ((Ground*)go)->GetPosition().y;
			rootNode[go->GetName()] = node;
		}
	}

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, rootNode);

	std::ofstream ofile("maps/"+currentFileName);

	if (ofile.is_open()) {
		ofile << json_file;
		ofile.close();
	}
}

void MapToolScene::LoadData(const std::string& fileName)
{
}

void MapToolScene::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
}

void MapToolScene::Draw(sf::RenderWindow& window)
{
	SortGameObjects();

	window.setView(worldView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer >= UILayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}

	for (auto& cell : cells)
	{
		window.draw(cell);
	}

	window.setView(uiView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer < UILayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}

}
