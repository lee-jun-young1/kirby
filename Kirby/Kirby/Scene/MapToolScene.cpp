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

	Json::Value mapData = LoadFromJsonFile("sprites/map/Green_Green_Data.json");
	sf::Vector2f buttonPosition = { menuBase->GetPosition().x, menuBase->GetSize().y * 0.2f };
	for (int i = 0; i < mapData["Palettes"].size(); i++)
	{
		Json::Value palette = mapData["Palettes"][i];
		UIButton* button = (UIButton*)AddGameObject(new UIButton(mapData["Path"].asString(), palette["PaletteID"].asString()));
		sf::IntRect rect = { palette["Position"]["x"].asInt(), palette["Position"]["y"].asInt(), (int)cellSize.x, (int)cellSize.y };
		Category cate = (Category)palette["Category"].asInt();
		button->SetOrigin(Origins::TL);
		button->SetCategory(cate);
		button->sprite.setTextureRect(rect);
		button->sprite.setScale(paletteScale);
		button->sortLayer = UILayer + palette["Layer"].asInt();
		if (i % 6 == 0)
		{
			buttonPosition.x = menuBase->GetPosition().x;
			buttonPosition.y += cellSize.y * paletteScale.y;
		}
		else
		{
			buttonPosition.x += cellSize.x * paletteScale.x;
		}
		button->SetPosition(buttonPosition);
		button->additionalData = palette;
		button->OnClick = [this, button]() {
			SelectGameObject(button);
		};
	}
	Scene::Enter();

	UIButton* saveBtn = (UIButton*)AddGameObject(new UIButton("sprites/button/button_save.png", "Save"));
	saveBtn->sprite.setTexture(*Resources.GetTexture(saveBtn->textureID));
	saveBtn->sprite.setScale({ 0.2f, 0.2f });
	saveBtn->sortLayer = UILayer + 100;
	saveBtn->SetOrigin(Origins::TL);
	saveBtn->SetPosition({ menuBase->GetPosition().x, 0 });
	saveBtn->OnClick = [this]() {
		SaveData(GetSaveFilePathWithOpenWindow());
	};

	UIButton* loadBtn = (UIButton*)AddGameObject(new UIButton("sprites/button/button_load.png", "Save"));
	loadBtn->sprite.setTexture(*Resources.GetTexture(loadBtn->textureID));
	loadBtn->sprite.setScale({ 0.2f, 0.2f });
	loadBtn->sortLayer = UILayer + 100;
	loadBtn->SetOrigin(Origins::TL);
	loadBtn->SetPosition({ saveBtn->GetPosition().x + saveBtn->GetSize().x * 0.2f, 0 });
	loadBtn->OnClick = [this]() {
		LoadData(GetLoadFilePathWithOpenWindow());
	};

	UIButton* clearBtn = (UIButton*)AddGameObject(new UIButton("sprites/button/button_clear.png", "Save"));
	clearBtn->sprite.setTexture(*Resources.GetTexture(clearBtn->textureID));
	clearBtn->sprite.setScale({ 0.2f, 0.2f });
	clearBtn->sortLayer = UILayer + 100;
	clearBtn->SetOrigin(Origins::TL);
	clearBtn->SetPosition({ loadBtn->GetPosition().x + loadBtn->GetSize().x * 0.2f, 0 });
	clearBtn->OnClick = [this]() {
		ClearCells();
	};
	Reset();
}

MapToolCell* MapToolScene::GetCell(const sf::Vector2f& position)
{
	for (auto& row : cells)
	{
		for (auto& col: row)
		{
			if (col.GetGlobalBounds().contains(position))
			{
				return &col;
			};
		}
	}
	return nullptr;
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
	}
	
	SpriteGO* instance = (SpriteGO*)AddGameObject(new SpriteGO(*gameObject));
	instance->sprite.setScale({ 1.f, 1.f });
	instance->sprite.setColor(sf::Color(255,255,255,128));
	instance->SetOrigin(Origins::TL);
	instance->SetActive(true);
	SetLayer(instance->sortLayer - UILayer);
	instance->sortLayer = UILayer - 1;
	currentGO = instance;
}

void MapToolScene::ClearCells()
{
	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.RemoveAllGameObject();
		}
	}
}

void MapToolScene::ClearCellsByCategory(const Category& cate)
{
	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.RemoveAllGameObjectByCategory(cate);
		}
	}
}

void MapToolScene::Init()
{
	Scene::Init();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	
	//윈도우 가운데로
	FRAMEWORK.GetWindow().setPosition(sf::Vector2i((1920 - windowSize.x * 4.f) / 2, (1080 - windowSize.y * 4.f) / 2));

	originalSize = { 24 * 20, 24 * 20 };
	mapSize = originalSize;
	TextGameObj* layerText = (TextGameObj*)AddGameObject(new TextGameObj("fonts/D2Coding.ttc", 12, "layer"));
	layerText->SetFillColor(sf::Color::Magenta);
	layerText->sortLayer = 999;
	layerText->SetPosition(10.f, 10.f);
	SetLayer(layer);

	cellHorizontalCount = floor(mapSize.x / cellSize.x);
	cellVerticalCount = floor(mapSize.y / cellSize.y);
	for (int i = 0; i < cellVerticalCount; i++)
	{
		std::vector<MapToolCell> row;
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			MapToolCell cell;
			cell.SetSize(cellSize);
			cell.SetPosition({j * cellSize.x, i * cellSize.y});
			row.push_back(cell);
		}
		cells.push_back(row);
	}

	auto size = FRAMEWORK.GetWindowSize();
	menuBase = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("MenuBase"));
	menuBase->SetSize({ size.x * 0.3f, size.y });
	menuBase->SetFillColor(sf::Color::Green);
	menuBase->sortLayer = UILayer;
	menuBase->SetOrigin(Origins::TL);
	menuBase->SetPosition({ size.x * 0.7f, 0.f });

}

void MapToolScene::Update(float dt)
{
	Scene::Update(dt);
	sf::Vector2f viewportPos = worldView.getCenter() - worldView.getSize() * 0.5f ;
	sf::Vector2f cellOrigin = { (float)((int)viewportPos.x % (int)cellSize.x), (float)((int)viewportPos.y % (int)cellSize.y) };
	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.SetOrigin(cellOrigin);
		}
	}

	//Move
	if (Input.GetKey(sf::Keyboard::Numpad8) && worldView.getCenter().y - (worldView.getSize().y * 0.5f) > 0.0f)
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y - uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::Numpad2) && worldView.getCenter().y + (worldView.getSize().y * 0.5f) < mapSize.y)
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y + uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::Numpad4) && worldView.getCenter().x - (worldView.getSize().x * 0.5f) > 0.0f)
	{
		worldView.setCenter(worldView.getCenter().x - uiSpeed * dt, worldView.getCenter().y);
	}
	if (Input.GetKey(sf::Keyboard::Numpad6) && worldView.getCenter().x + (worldView.getSize().x * 0.5f) < mapSize.x + menuBase->GetSize().x)
	{
		worldView.setCenter(worldView.getCenter().x + uiSpeed * dt, worldView.getCenter().y);
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
		SetLayer(layer);
	}


	//SelectTest
	if (Input.GetKeyDown(sf::Keyboard::Num1))
	{
		SelectGameObject((SpriteGO*)FindGameObject("row-6-column-6"));
	}

	auto cell = GetCell(ScreenToWorldPosition(Input.GetMousePosition()) - cellOrigin);
	if (menuBase->GetGlobalBounds().contains(ScreenToUIPosition(Input.GetMousePosition())))
	{
		cell = nullptr;
	}
	if (cell != nullptr)
	{
		//snap
		if (currentGO != nullptr)
		{
			currentGO->SetPosition(cell->GetPosition());
		}

		//Add
		if (Input.GetMouseButton(sf::Mouse::Left) && currentGO != nullptr)
		{
			if (currentGO->GetCategory() == Category::Player)
			{
				ClearCellsByCategory(currentGO->GetCategory());
			}
			if (currentGO->GetCategory() != Category::Door)
			{
				cell->AddGameObject(currentGO, layer);
			}
		}
		if (Input.GetMouseButtonDown(sf::Mouse::Left) && currentGO != nullptr)
		{
			if (currentGO->GetCategory() == Category::Door)
			{
				doorMovePosition = currentGO->GetPosition();
				currentGO->additionalData["MovePosition"]["x"] = currentGO->GetPosition().x;
				currentGO->additionalData["MovePosition"]["y"] = currentGO->GetPosition().y;
				prevGO = cell->AddGameObject(currentGO, layer);
			}
		}
		if (Input.GetMouseButtonUp(sf::Mouse::Left) && currentGO != nullptr)
		{
			if (currentGO->GetCategory() == Category::Door)
			{
				currentGO->additionalData["MovePosition"]["x"] = doorMovePosition.x;
				currentGO->additionalData["MovePosition"]["y"] = doorMovePosition.y;
				prevGO->additionalData["MovePosition"]["x"] = currentGO->GetPosition().x;
				prevGO->additionalData["MovePosition"]["y"] = currentGO->GetPosition().y;
				cell->AddGameObject(currentGO, layer);
			}
		}

		//Remove
		if (Input.GetMouseButton(sf::Mouse::Right))
		{
			cell->RemoveGameObject(layer);
		}
	}


	//Clear
	if (Input.GetKeyDown(sf::Keyboard::F1))
	{
		ClearCells();
	}

	//Save
	if (Input.GetKeyDown(sf::Keyboard::F5))
	{
		std::wstring filePath = GetSaveFilePathWithOpenWindow();
		std::wcout << filePath << std::endl;
		SaveData(filePath);
	}
	//Load
	if (Input.GetKeyDown(sf::Keyboard::F6))
	{
		std::wstring filePath = GetLoadFilePathWithOpenWindow();
		std::wcout << filePath << std::endl;
		LoadData(filePath);
	}

	//Zoom
	//if (Input.GetMouseScrollDelta() != 0)
	//{
	//	std::cout << Input.GetMouseScrollDelta() << std::endl;
	//	worldView.zoom(1.f - Input.GetMouseScrollDelta() * 0.1f);
	//}

	//MapSize
	if (Input.GetKeyDown(sf::Keyboard::Add))
	{
		ReSizeMap(true);
	}
	if (Input.GetKeyDown(sf::Keyboard::Subtract))
	{
		ReSizeMap(false);
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

	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.DrawGameObject(window, layer, drawCurrentLayerOnly);
		}
	}

	window.setView(uiView);

	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.Draw(window);
		}
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
	if (path == "")
	{
		return;
	}
	Json::Value rootNode;
	rootNode["Stage"] = (int)stageIndex;
	rootNode["MapSize"]["x"] = mapSize.x;
	rootNode["MapSize"]["y"] = mapSize.y;

	Json::Value playerNode;
	Json::Value itemNodes;
	Json::Value enemyNodes;
	Json::Value doorNodes;
	Json::Value groundNodes;
	Json::Value ambientObjectNodes;

	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			if (col.GetGameObjects().size() < 1)
			{
				continue;
			}
			for (auto& go : col.GetGameObjects())
			{
				Json::Value node;
				node["PaletteID"] = go->GetName();
				node["Position"]["x"] = go->GetPosition().x;
				node["Position"]["y"] = go->GetPosition().y;
				node["SortLayer"] = go->sortLayer;

				switch (go->GetCategory())
				{
				case Category::None:
					break;
				case Category::Player:
					playerNode = node;
					break;
				case Category::Item:
					node["Type"] = ((SpriteGO*)go)->additionalData["Type"].asInt();
					itemNodes.append(node);
					break;
				case Category::Enemy:
					node["Type"] = ((SpriteGO*)go)->additionalData["Type"].asInt();
					enemyNodes.append(node);
					break;
				case Category::Door:
					node["Type"] = ((SpriteGO*)go)->additionalData["Type"].asInt();
					node["MovePosition"]["x"] = ((SpriteGO*)go)->additionalData["MovePosition"]["x"].asFloat();
					node["MovePosition"]["y"] = ((SpriteGO*)go)->additionalData["MovePosition"]["y"].asFloat();
					doorNodes.append(node);
					break;
				case Category::Ground:
					node["GroundIndex"] = ((SpriteGO*)go)->additionalData["GroundIndex"].asInt();
					groundNodes.append(node);
					break;
				case Category::AmbientObject:
					ambientObjectNodes.append(node);
					break;
				}
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
	if (path == "")
	{
		return;
	}
	std::ifstream ifile(path);
	Json::Value rootNode;
	if (ifile.is_open())
	{
		ifile >> rootNode;
		ifile.close();
	}
	else
	{
		std::wcout << "File Open Error! Path: " << path << std::endl;
		return;
	}

	ClearCells();
	int AddColumnCount = floor(rootNode["MapSize"]["x"].asInt() - originalSize.x) / cellSize.x;
	int AddRowCount = floor(rootNode["MapSize"]["y"].asInt() - originalSize.y) / cellSize.y;
	for (int j = 0; j < AddColumnCount; j++)
	{
		AddColumn();
	}
	for (int i = 0; i < AddRowCount; i++)
	{
		AddRow();
	}

	Json::Value playerNode = rootNode["Player"];
	Json::Value itemNodes = rootNode["Item"];
	Json::Value enemyNodes = rootNode["Enemy"];
	Json::Value doorNodes = rootNode["Door"];
	Json::Value groundNodes = rootNode["Ground"];
	Json::Value ambientObjectNodes = rootNode["AmbientObject"];

	MapToolCell* cell;
	sf::Vector2f loadPosition;
	int loadLayer = 0;

	SpriteGO* player = CopyUIButton(playerNode["PaletteID"].asString());
	if (player != nullptr)
	{
		loadPosition = { playerNode["Position"]["x"].asFloat(), playerNode["Position"]["y"].asFloat()};
		player->sprite.setScale({1.f, 1.f});
		player->SetPosition(loadPosition);
		cell = GetCell(loadPosition);
		cell->AddGameObject(player, playerNode["SortLayer"].asInt());
	}

	for (int i = 0; i < itemNodes.size(); i++)
	{
		Json::Value item = itemNodes[i];
		Item* go = (Item*)CopyUIButton(item["PaletteID"].asString());
		loadPosition = { item["Position"]["x"].asFloat(), item["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		go->SetItemType((ItemType)item["type"].asInt());
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, item["SortLayer"].asInt());
	}

	for (int i = 0; i < enemyNodes.size(); i++)
	{
		Json::Value item = enemyNodes[i];
		Enemy* go = (Enemy*)CopyUIButton(item["PaletteID"].asString());
		loadPosition = { item["Position"]["x"].asFloat(), item["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		go->SetEnemyType((EnemyType)item["type"].asInt());
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, item["SortLayer"].asInt());
	}

	for (int i = 0; i < doorNodes.size(); i++)
	{
		Json::Value item = doorNodes[i];
		SpriteGO* go = CopyUIButton(item["PaletteID"].asString());
		loadPosition = { item["Position"]["x"].asFloat(), item["Position"]["y"].asFloat() };
		go->additionalData["MovePosition"]["x"] = item["MovePosition"]["x"];
		go->additionalData["MovePosition"]["y"] = item["MovePosition"]["y"];
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, item["SortLayer"].asInt());
	}

	for (int i = 0; i < groundNodes.size(); i++)
	{
		Json::Value item = groundNodes[i];
		Ground* go = (Ground*)CopyUIButton(item["PaletteID"].asString());
		loadPosition = { item["Position"]["x"].asFloat(), item["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		go->SetGroundIndex(item["GroundIndex"].asInt());
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, item["SortLayer"].asInt());
	}

	for (int i = 0; i < ambientObjectNodes.size(); i++)
	{
		Json::Value item = ambientObjectNodes[i];
		AmbientObject* go = (AmbientObject*)CopyUIButton(item["PaletteID"].asString());
		loadPosition = { item["Position"]["x"].asFloat(), item["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, item["SortLayer"].asInt());
	}
}
const std::wstring MapToolScene::GetLoadFilePathWithOpenWindow()
{
	OPENFILENAME OFN;
	TCHAR filePathName[100] = L"";
	TCHAR lpstrFile[100] = L"";
	static TCHAR filter[] = L"JSON 파일\0*.json\0모든 파일\0*.*";

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

const std::wstring MapToolScene::GetSaveFilePathWithOpenWindow()
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

SpriteGO* MapToolScene::CopyUIButton(const std::string& paletteID)
{
	SpriteGO* findGo = (SpriteGO*)FindGameObject(paletteID);
	if (findGo == nullptr)
	{
		return nullptr;
	}
	SpriteGO* instance = new SpriteGO(*findGo);

	return instance;
}

void MapToolScene::SetLayer(int layer)
{
	this->layer = layer;
	TextGameObj* findGo = (TextGameObj*)FindGameObject("layer");
	std::stringstream ss;
	ss << "Layer: " << this->layer;
	if (drawCurrentLayerOnly)
	{
		ss << " Only";
	}
	findGo->SetString(ss.str());
}

void MapToolScene::ReSizeMap(bool expand)
{
	std::cout << cells.size() * cells[cells.size() - 1].size() << std::endl;
	if (expand)
	{
		AddColumn();
		AddRow();
	}
	else
	{
		if (cellHorizontalCount > floor(originalSize.x / cellSize.x) && cellVerticalCount > floor(originalSize.x / cellSize.x))
		{
			DelColumn();
			DelRow();

			//worldView.setCenter(worldView.getCenter() - cellSize);
		}
	}

	std::cout << cells.size() * cells[cells.size() - 1].size() << std::endl;
}

void MapToolScene::AddColumn()
{
	//열 추가
	for (int i = 0; i < cellVerticalCount; i++)
	{
		MapToolCell cell;
		cell.SetSize(cellSize);
		cell.SetPosition({ cellHorizontalCount * cellSize.x, i * cellSize.y });
		cells[i].push_back(cell);
	}
	cellHorizontalCount++;
	mapSize.x += (int)cellSize.x;
}
void MapToolScene::DelColumn()
{
	// 열 제거
	for (int i = 0; i < cellVerticalCount; i++)
	{
		for (auto go : cells[i][cellHorizontalCount - 1].GetGameObjects())
		{
			delete go;
		}
		cells[i].pop_back();
	}
	cellHorizontalCount--;
	mapSize.x -= (int)cellSize.x;
}
void MapToolScene::AddRow()
{
	//행 추가
	std::vector<MapToolCell> row;
	for (int i = 0; i < cellHorizontalCount; i++)
	{
		MapToolCell cell;
		cell.SetSize(cellSize);
		cell.SetPosition({ i * cellSize.x, cellVerticalCount * cellSize.y });
		row.push_back(cell);
	}
	cells.push_back(row);
	cellVerticalCount++;
	mapSize.y += (int)cellSize.y;
}
void MapToolScene::DelRow()
{
	// 행 제거
	for (auto& cell : cells[cellVerticalCount - 1])
	{
		for (auto go : cell.GetGameObjects())
		{
			delete go;
		}
	}
	cells.pop_back();
	cellVerticalCount--;
	mapSize.y -= (int)cellSize.y;
}