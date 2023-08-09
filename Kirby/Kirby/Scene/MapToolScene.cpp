#include "stdafx.h"
#include "MapToolScene.h"
#include "GameObject.h"
#include "TextGameObj.h"
#include "Utils.h"
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
#include "SpriteGO.h"
#include "UIButton.h"
#include <fstream>
#include <commdlg.h>

MapToolScene::MapToolScene() : Scene(SceneId::MapTool)
{
	sceneName = "MapToolScene";
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

	RectangleShapeGO* base = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Base"));
	base->SetSize({ size.x * 0.3f, size.y });
	base->SetFillColor(sf::Color::Green);
	base->sortLayer = UILayer;
	base->SetOrigin(Origins::TL);
	base->SetPosition({ size.x * 0.7f, 0.f });

	sf::Vector2f buttonSpace = { 2.f, 1.f };
	Json::Value mapData = LoadFromJsonFile("sprites/map/Green_Green_Data.json");
	std::cout << mapData["path"].asString() << std::endl;
	for (int i = 0; i < mapData["cells"].size(); i++)
	{
		Json::Value cell = mapData["cells"][i];
		std::cout << cell["name"] << std::endl;
		UIButton* button = (UIButton*)AddGameObject(new UIButton(mapData["path"].asString(), cell["name"].asString()));
		sf::IntRect rect = { cell["position"]["x"].asInt(), cell["position"]["y"].asInt(), (int)cellSize.x, (int)cellSize.y };
		button->sprite.setTextureRect(rect);
		button->sprite.setScale({0.5f, 0.5f});
		button->sortLayer = UILayer + cell["layer"].asInt() + 1; //1은 임시
		button->OnClick = [this, button]() {
			SelectGameObject(button);
		};

		sf::Vector2f buttonPosition = { base->GetPosition().x + rect.left * 0.5f, base->GetSize().y * 0.3f + rect.top * 0.5f };


		button->SetPosition(buttonPosition);
		//button->SetPosition({ base->GetPosition().x + rect.left * 0.5f, base->GetSize().y * 0.3f + rect.top * 0.5f});

		//for (int j = 0; j < cell["friend"].size(); j++)
		//{
		//	Json::Value friendData = cell["friend"][j];
		//}
	}
	Scene::Enter();
	Reset();
}

MapToolCell* MapToolScene::GetCell(const sf::Vector2f& position)
{
	for (auto& cell : cells)
	{
		if (cell.GetGlobalBounds().contains(position))
		{
			//std::cout
			//	<< "X: " << (int)cell.GetGlobalBounds().left
			//	<< " Y: " << (int)cell.GetGlobalBounds().top
			//	<< std::endl;
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

void MapToolScene::SelectGameObject(SpriteGO* gameObject)
{
	if (gameObject == nullptr)
	{
		return;
	}

	if (currentGO != nullptr)
	{
		currentGO->SetActive(false);
		currentGO = nullptr;
		return;
	}
	
	SpriteGO* instance = (SpriteGO*)AddGameObject(new SpriteGO(*gameObject));
	currentGO = instance;
	currentGO->sprite.setScale({ 1.f, 1.f });
	currentGO->SetActive(true);
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
	Scene::Update(dt);
	sf::Vector2f viewportPos = worldView.getCenter() - worldView.getSize() * 0.5f ;
	sf::Vector2f cellOrigin = { (float)((int)viewportPos.x % (int)cellSize.x), (float)((int)viewportPos.y % (int)cellSize.y) };
	for (int i = 0; i < cellVerticalCount; i++)
	{
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			cells[i * cellHorizontalCount + j].SetOrigin(cellOrigin);
		}
	}

	//Move
	worldMovement = worldView.getCenter();
	if (Input.GetKey(sf::Keyboard::Numpad8))
	{
		worldView.setCenter(worldMovement.x, worldMovement.y - uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::Numpad2))
	{
		worldView.setCenter(worldMovement.x, worldMovement.y + uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::Numpad4))
	{
		worldView.setCenter(worldMovement.x - uiSpeed * dt, worldMovement.y);
	}
	if (Input.GetKey(sf::Keyboard::Numpad6))
	{
		worldView.setCenter(worldMovement.x + uiSpeed * dt, worldMovement.y);
	}

	//Layer
	if (Input.GetKeyDown(sf::Keyboard::PageUp))
	{
		SetLayer(++layer);
	}
	if (Input.GetKeyDown(sf::Keyboard::PageDown))
	{
		SetLayer(--layer);
	}
	if (Input.GetKeyDown(sf::Keyboard::Home))
	{
		drawCurrentLayerOnly = !drawCurrentLayerOnly;
	}


	//Select
	if (Input.GetKeyDown(sf::Keyboard::Num1))
	{
		RectangleShapeGO* rect = (RectangleShapeGO*)FindGameObject("testGO");
		SelectGameObject(rect);
	}

	auto cell = GetCell(ScreenToWorldPosition(Input.GetMousePosition()) - cellOrigin);
	RectangleShapeGO* base = (RectangleShapeGO*)FindGameObject("Base");
	if (base->GetGlobalBounds().contains(ScreenToWorldPosition(Input.GetMousePosition())))
	{
		cell = nullptr;
	}
	if (cell == nullptr)
	{
		return;
	}
	if (currentGameObject != nullptr)
	{
		currentGameObject->SetPosition(cell->GetPosition());
	}
	if (currentGO != nullptr)
	{
		currentGO->SetPosition(cell->GetPosition());
	}
	//Add
	if (Input.GetMouseButton(sf::Mouse::Left) )
	{
		//cell->AddGameObject(currentGameObject, layer);
		cell->AddGameObject(currentGO, layer);
	}

	//Remove
	if (Input.GetMouseButton(sf::Mouse::Right))
	{
		cell->RemoveGameObject(layer);
	}

	//Save
	if (Input.GetKeyDown(sf::Keyboard::F5))
	{
		std::wstring filePath = GetSaveFileNameWithOpenWindow();
		std::wcout << filePath << std::endl;
		SaveData(filePath);
	}
	//Load
	if (Input.GetKeyDown(sf::Keyboard::F6))
	{
		std::wstring filePath = GetFilePathWithOpenWindow();
		std::wcout << filePath << std::endl;
		LoadData(filePath);
	}

	if (Input.GetMouseWheelMovement() != 0)
	{
		std::cout << Input.GetMouseWheelMovement() << std::endl;
		worldView.zoom(Input.GetMouseWheelMovement());
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

void MapToolScene::SaveData(const std::wstring& path)
{
	Json::Value rootNode;
	rootNode["Stage"] = (int)stageIndex;

	Json::Value playerNode;
	Json::Value itemNodes;
	Json::Value enemyNodes;
	Json::Value doorNodes;
	Json::Value groundNodes;
	Json::Value ambientObjectNodes;

	for (auto cell : cells)
	{
		for (auto& go : cell.GetGameObjects())
		{
			Json::Value node;
			std::string name = go->GetName();
		
			node["PositionX"] = go->GetPosition().x;
			node["PositionY"] = go->GetPosition().y;
			node["SortLayer"] = go->sortLayer + layer;

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
			else if (go->GetName() == "AmbientObject")
			{
				ambientObjectNodes.append(node);
			}
		}
	}

	rootNode["Player"] = playerNode;
	rootNode["Item"] = itemNodes;
	rootNode["Enemy"] = enemyNodes;
	rootNode["Door"] = doorNodes;
	rootNode["Ground"] = groundNodes;
	rootNode["AmbientObject"] = ambientObjectNodes;

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, rootNode);
	
	std::ofstream ofile(path);

	if (ofile.is_open()) {
		ofile << json_file;
		ofile.close();
	}
}

void MapToolScene::LoadData(const std::wstring& path)
{
	std::ifstream ifile(path);
	Json::Value rootNode;
	if (ifile.is_open())
	{
		ifile >> rootNode;
		ifile.close();
	}
	
	Json::Value playerNode = rootNode["Player"];
	Json::Value itemNodes = rootNode["Item"];
	Json::Value enemyNodes = rootNode["Enemy"];
	Json::Value doorNodes = rootNode["Door"];
	Json::Value groundNodes = rootNode["Ground"];
	Json::Value ambientObjectNodes = rootNode["AmbientObject"];

	Player* player = (Player*)AddGameObject(new Player("Player"));
	player->sortLayer = playerNode["SortLayer"].asInt();
	player->SetPosition(playerNode["PositionX"].asFloat(), playerNode["PositionY"].asFloat());

	for (int i = 0; i < itemNodes.size(); i++)
	{
		Json::Value item = itemNodes[i];
		Item* go = (Item*)AddGameObject(new Item("Item"));
		go->SetPosition({ item["PositionX"].asFloat(), item["PositionY"].asFloat() });
		go->sortLayer = item["SortLayer"].asInt();
		go->SetItemType((ItemType)item["Type"].asInt());
	}
	for (int i = 0; i < enemyNodes.size(); i++)
	{
		Json::Value item = enemyNodes[i];
		Enemy* go = (Enemy*)AddGameObject(new Enemy("Enemy"));
		go->SetPosition({ item["PositionX"].asFloat(), item["PositionY"].asFloat() });
		go->sortLayer = item["SortLayer"].asInt();
		go->SetEnemyType((EnemyType)item["Type"].asInt());
	}
	for (int i = 0; i < doorNodes.size(); i++)
	{
		Json::Value item = doorNodes[i];
		Door* go = (Door*)AddGameObject(new Door("Door"));
		go->SetPosition({ item["PositionX"].asFloat(), item["PositionY"].asFloat() });
		go->sortLayer = item["SortLayer"].asInt();
		go->SetDoorType((DoorType)item["Type"].asInt());
		go->SetMovePosition({ item["MovePositionX"].asFloat(), item["MovePositionY"].asFloat() });
	}
	for (int i = 0; i < groundNodes.size(); i++)
	{
		Json::Value item = groundNodes[i];
		Ground* go = (Ground*)AddGameObject(new Ground("Ground"));
		go->SetPosition({ item["PositionX"].asFloat(), item["PositionY"].asFloat() });
		go->sortLayer = item["SortLayer"].asInt();
		go->SetGroundIndex(item["GroundIndex"].asInt());
	}
	for (int i = 0; i < ambientObjectNodes.size(); i++)
	{
		Json::Value item = ambientObjectNodes[i];
		AmbientObject* go = (AmbientObject*)AddGameObject(new AmbientObject("AmbientObject"));
		go->SetPosition({ item["PositionX"].asFloat(), item["PositionY"].asFloat() });
		go->sortLayer = item["SortLayer"].asInt();
	}

}

const std::wstring MapToolScene::GetFilePathWithOpenWindow()
{
	OPENFILENAME OFN;
	TCHAR filePathName[100] = L"";
	TCHAR lpstrFile[100] = L"";
	static TCHAR filter[] = L"모든 파일\0*.*\0JSON 파일\0*.json";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = FRAMEWORK.GetHWnd();
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = L".";

	if (GetOpenFileName(&OFN) != 0)
	{
		//wsprintf(filePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
		//MessageBox(FRAMEWORK.GetHWnd(), filePathName, L"열기 선택", MB_OK);

		return OFN.lpstrFile;
	}

	return L"";
}

const std::wstring MapToolScene::GetSaveFileNameWithOpenWindow()
{
	OPENFILENAME OFN;
	TCHAR filePathName[100] = L"";
	TCHAR lpstrFile[100] = L"";
	static TCHAR filter[] = L"모든 파일\0*.*\0JSON 파일\0*.json";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = FRAMEWORK.GetHWnd();
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = L".";
	OFN.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&OFN) != 0)
	{
		//wsprintf(filePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
		//MessageBox(FRAMEWORK.GetHWnd(), filePathName, L"열기 선택", MB_OK); 

		wstring path = OFN.lpstrFile;
		if (!Utils::Contains(path, '.'))
		{
			path += L".json";
		}
		return path;
	}

	return L"";
}

Json::Value MapToolScene::LoadFromJsonFile(const std::string& path)
{
	std::ifstream ifile(path);
	Json::Value rootNode;
	if (ifile.is_open())
	{
		ifile >> rootNode;
		ifile.close();
	}
	return rootNode;
}

void MapToolScene::SetLayer(int layer)
{
	this->layer = layer;
	TextGameObj* findGo = (TextGameObj*)FindGameObject("layer");
	std::stringstream ss;
	ss << "Layer: " << this->layer;
	findGo->SetString(ss.str());
}
