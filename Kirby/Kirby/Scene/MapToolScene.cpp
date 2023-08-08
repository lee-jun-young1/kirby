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
#include "InputManager.h"
#include "RectangleShapeGO.h"
#include <fstream>
#include <TextGameObj.h>

MapToolScene::MapToolScene() : Scene(SceneId::MapTool)
{
	sceneName = "MapToolScene";
	currentFileName = "stage_1.json";
}

MapToolScene::~MapToolScene()
{
	Release();
}

void MapToolScene::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f screenCenter = { size.x * 0.5f, size.y * 0.5f} ;
	worldView.setSize(size);
	worldView.setCenter(screenCenter.x, screenCenter.y);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	//test
	RectangleShapeGO* rect = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("testGO"));
	rect->SetSize(cellSize);
	rect->SetFillColor(sf::Color::Green);
	rect->sortLayer = 99;
	rect->SetActive(false);
	rect->SetOrigin(Origins::TL);

	Scene::Enter();
	Reset();
}

void MapToolScene::SaveData()
{
	Json::Value rootNode;
	rootNode["Stage"] = (int)stageIndex;

	Json::Value playerNode;
	Json::Value itemNodes;
	Json::Value enemyNodes;
	Json::Value doorNodes;
	Json::Value groundNodes;

	for (auto go : gameObjects)
	{
		Json::Value node;
		std::string name = go->GetName();
		node["PositionX"] = go->GetPosition().x;
		node["PositionY"] = go->GetPosition().y;
		node["SortLayer"] = go->sortLayer;
		
		if (go->GetName() == "Player")
		{
			playerNode = node;
		}
		else if (go->GetName() == "Item")
		{
			node["Type"] = (int)((Item*)go)->GetItemType();
			itemNodes.append(node);
		}
		else if (go->GetName() == "Enemy")
		{
			node["Type"] = (int)((Enemy*)go)->GetEnemyType();
			enemyNodes.append(node);
		}
		else if (go->GetName() == "Door")
		{
			node["Type"] = (int)((Enemy*)go)->GetEnemyType();
			node["MovePositionX"] = ((Door*)go)->GetMovePosition().x;
			node["MovePositionY"] = ((Door*)go)->GetMovePosition().y;
			doorNodes.append(node);
		}
		else if (go->GetName() == "Ground")
		{
			node["GroundIndex"] = ((Ground*)go)->GetGroundIndex();
			groundNodes.append(node);
		}
	}

	rootNode["Player"] = playerNode;
	rootNode["Item"] = itemNodes;
	rootNode["Enemy"] = enemyNodes;
	rootNode["Door"] = doorNodes;
	rootNode["Ground"] = groundNodes;

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

MapToolCell* MapToolScene::GetCell(const sf::Vector2f& position)
{
	for (auto& cell : cells)
	{
		if (cell.GetGlobalBounds().contains(position))
		{
			std::cout
				<< "X: " << (int)cell.GetGlobalBounds().left
				<< " Y: " << (int)cell.GetGlobalBounds().top
				<< std::endl;
			return &cell;
		};
	}
	return nullptr;
}

void MapToolScene::SelectGameObject(RectangleShapeGO* gameObject)
{
	if (gameObject == nullptr)
	{
		return;
	}

	if (currentGameObject != nullptr)
	{
		currentGameObject->SetActive(false);
		if (currentGameObject == gameObject)
		{
			currentGameObject = nullptr;
			return;
		}
	}

	currentGameObject = gameObject;
	currentGameObject->SetActive(true);
}

void MapToolScene::Init()
{
	Scene::Init();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	TextGameObj* layerText = (TextGameObj*)AddGameObject(new TextGameObj("fonts/D2Coding.ttc", 12, "layer"));
	layerText->SetFillColor(sf::Color::Magenta);
	layerText->sortLayer = 999;
	layerText->SetPosition(10.f, 10.f);

	cellHorizontalCount = (windowSize.x / cellSize.x) + 2;
	cellVerticalCount = (windowSize.y / cellSize.y) + 2;
	for (int i = 0; i < cellVerticalCount; i++)
	{
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			MapToolCell cell;
			cell.SetSize(cellSize);
			cell.SetFillColor(sf::Color::Transparent);
			cell.SetOutlineThickness(0.5f);
			cell.SetOutlineColor(sf::Color::White);
			cell.SetPosition({j * cellSize.x, i * cellSize.y});
			cells.push_back(cell);
		}
	}
}

void MapToolScene::Update(float dt)
{
	TextGameObj* findGo = (TextGameObj*)FindGameObject("layer");
	std::stringstream ss;
	ss << "Layer: " << layer;
	findGo->text.setString(ss.str());

	sf::Vector2f viewportPos = worldView.getCenter() - worldView.getSize() * 0.5f ;
	sf::Vector2f origin = { (float)((int)viewportPos.x % (int)cellSize.x), (float)((int)viewportPos.y % (int)cellSize.y) };
	for (int i = 0; i < cellVerticalCount; i++)
	{
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			cells[i * cellHorizontalCount + j].SetOrigin(origin);
		}
	}

	if (Input.GetKeyDown(sf::Keyboard::F5))
	{
		SaveData();
	}

	if (Input.GetKeyDown(sf::Keyboard::Num1))
	{
		//select
		RectangleShapeGO* rect = (RectangleShapeGO*)FindGameObject("testGO");
		SelectGameObject(rect);
	}

	//Move
	if (Input.GetKey(sf::Keyboard::Numpad8))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y - uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::Numpad2))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y + uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::Numpad4))
	{
		worldView.setCenter(worldView.getCenter().x - uiSpeed * dt, worldView.getCenter().y);
	}
	if (Input.GetKey(sf::Keyboard::Numpad6))
	{
		worldView.setCenter(worldView.getCenter().x + uiSpeed * dt, worldView.getCenter().y);
	}

	//Move
	if (Input.GetKeyDown(sf::Keyboard::PageUp))
	{
		layer++;
	}
	if (Input.GetKeyDown(sf::Keyboard::PageDown))
	{
		layer--;
	}

	if (Input.GetKeyDown(sf::Keyboard::Home))
	{
		drawCurrentLayerOnly = !drawCurrentLayerOnly;
	}

	auto cell = GetCell(ScreenToWorldPosition(Input.GetMousePosition()) - origin);
	if (cell == nullptr)
	{
		return;
	}
	if (currentGameObject != nullptr)
	{
		currentGameObject->SetPosition(cell->GetPosition());
	}

	if (Input.GetMouseButton(sf::Mouse::Left))
	{
		cell->AddGameObject(currentGameObject, layer);
	}

	if (Input.GetMouseButton(sf::Mouse::Right))
	{
		//remove
		cell->RemoveGameObject(layer);
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

	for (auto& cell : cells)
	{
		cell.DrawGameObject(window, layer, drawCurrentLayerOnly);
	}

	window.setView(uiView);

	for (auto& cell : cells)
	{
		cell.Draw(window);
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
