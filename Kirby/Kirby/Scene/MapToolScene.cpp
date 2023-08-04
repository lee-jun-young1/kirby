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

MapToolScene::MapToolScene() : Scene(SceneId::MapTool)
{
	sceneName = "TitleScene";
}

MapToolScene::~MapToolScene()
{
	Release();
}

void MapToolScene::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	auto screenCenter = size * 0.5f;
	worldView.setSize(size);
	worldView.setCenter(0.0f, 0.0f);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	Scene::Enter();
	Reset();
}

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
	cellHorizontalCount = (windowSize.x / cellSize.x) + 1;
	cellVerticalCount = (windowSize.y / cellSize.y) + 1;
	for (int i = 0; i < cellVerticalCount; i++)
	{
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			sf::RectangleShape shape;
			shape.setSize(cellSize);
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineThickness(1.0f);
			shape.setOutlineColor(sf::Color::White);
			shape.setPosition({j * cellSize.x, i * cellSize.y});
			cells.push_back(shape);
		}
	}
}

void MapToolScene::Update(float dt)
{
	
	for (int i = 0; i < cellVerticalCount; i++)
	{
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			//cells[i * cellHorizontalCount + j].setPosition(
			//	{ j * cellSize.x - (worldView.getViewport().left % cellSize.x),
			//	i * cellSize.y - (worldView.getViewport().top % cellSize.y) });
		}
	}
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
	window.setView(uiView);

	for (auto& cell : cells)
	{
		window.draw(cell);
	}


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

void MapToolScene::Release()
{
}

void MapToolScene::Reset()
{
}
