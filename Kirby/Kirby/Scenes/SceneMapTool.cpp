#include "stdafx.h"
#include "SceneMapTool.h"
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
#include <SceneManager.h>

SceneMapTool::SceneMapTool() : Scene(SceneId::MapTool)
{
	sceneName = "SceneMapTool";
}

SceneMapTool::~SceneMapTool()
{
	Release();
}

void SceneMapTool::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f screenCenter = { size.x * 0.5f, size.y * 0.5f} ;
	worldView.setSize(size);
	worldView.setCenter(screenCenter.x, screenCenter.y);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	paletteView.setSize(menuBase->GetSize());
	paletteView.setViewport(sf::FloatRect(0.7f, 0.f, 0.3f, 1.f));
	paletteView.setCenter({ menuBase->GetGlobalBounds().left + menuBase->GetGlobalBounds().width * 0.5f, menuBase->GetGlobalBounds().height * 0.5f});

	Json::Value mapData = LoadFromJsonFile("sprites/map/Green_Green_Data.json");
	mapPath = mapData["Path"].asString();
	sf::Vector2f buttonPosition = { menuBase->GetPosition().x, menuBase->GetSize().y * 0.2f };
	for (int i = 0; i < mapData["Palettes"].size(); i++)
	{
		Json::Value palette = mapData["Palettes"][i];
		UIButton* button = (UIButton*)AddGameObject(new UIButton(mapPath, palette["PaletteID"].asString()));
		sf::IntRect rect = { palette["Position"]["x"].asInt(), palette["Position"]["y"].asInt(), (int)cellSize.x, (int)cellSize.y };
		Category cate = (Category)palette["Category"].asInt();
		button->SetOrigin(Origins::TL);
		button->SetCategory(cate);
		button->sprite.setTextureRect(rect);
		button->sprite.setScale(paletteScale);
		button->sortLayer = paletteLayer + palette["Layer"].asInt();
		if (i % 6 == 0)
		{
			buttonPosition.x = menuBase->GetPosition().x;
			buttonPosition.y += cellSize.y * paletteScale.y + paletteSpace.x;
		}
		else
		{
			buttonPosition.x += cellSize.x * paletteScale.x + paletteSpace.y;
		}
		button->SetPosition((buttonPosition));
		button->additionalData = palette;
		button->OnClick = [this, button]() {
			SelectGameObject(button);
		};
		palettes.push_back(button);
	}
	Scene::Enter();

	UIButton* saveBtn = (UIButton*)AddGameObject(new UIButton("sprites/button/button_save.png", "Save"));
	saveBtn->sprite.setTexture(*Resources.GetTexture(saveBtn->textureID));
	saveBtn->sprite.setScale({ 0.2f, 0.2f });
	saveBtn->sortLayer = paletteLayer - 1;
	saveBtn->SetOrigin(Origins::TL);
	saveBtn->SetPosition({ menuBase->GetPosition().x, 0 });
	saveBtn->OnClick = [this]() {
		SaveData(GetSaveFilePathWithOpenWindow());
	};

	UIButton* loadBtn = (UIButton*)AddGameObject(new UIButton("sprites/button/button_load.png", "Save"));
	loadBtn->sprite.setTexture(*Resources.GetTexture(loadBtn->textureID));
	loadBtn->sprite.setScale({ 0.2f, 0.2f });
	loadBtn->sortLayer = paletteLayer - 1;
	loadBtn->SetOrigin(Origins::TL);
	loadBtn->SetPosition({ saveBtn->GetPosition().x + saveBtn->GetSize().x * 0.2f, 0 });
	loadBtn->OnClick = [this]() {
		LoadData(GetLoadFilePathWithOpenWindow());
	};

	UIButton* clearBtn = (UIButton*)AddGameObject(new UIButton("sprites/button/button_clear.png", "Save"));
	clearBtn->sprite.setTexture(*Resources.GetTexture(clearBtn->textureID));
	clearBtn->sprite.setScale({ 0.2f, 0.2f });
	clearBtn->sortLayer = paletteLayer - 1;
	clearBtn->SetOrigin(Origins::TL);
	clearBtn->SetPosition({ loadBtn->GetPosition().x + loadBtn->GetSize().x * 0.2f, 0 });
	clearBtn->OnClick = [this]() {
		ClearCells();
	};
	Reset();
}

MapToolCell* SceneMapTool::GetCell(const sf::Vector2f& position)
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

void SceneMapTool::SelectGameObject(SpriteGO* gameObject)
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
	instance->SetActive(true);
	instance->SetPosition(PalettePositionToScreen(instance->GetPosition()));
	SetLayer(instance->sortLayer - paletteLayer);
	instance->sortLayer = UILayer - 1;
	currentGO = instance;
}

void SceneMapTool::ClearCells()
{
	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.RemoveAllGameObject();
		}
	}

	//sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	//cellHorizontalCount = floor(mapSize.x / cellSize.x);
	//cellVerticalCount = floor(mapSize.y / cellSize.y);
	//for (int i = 0; i < cellVerticalCount; i++)
	//{
	//	std::vector<MapToolCell> row;
	//	for (int j = 0; j < cellHorizontalCount; j++)
	//	{
	//		MapToolCell cell;
	//		cell.SetSize(cellSize);
	//		cell.SetPosition({ j * cellSize.x, i * cellSize.y });
	//		row.push_back(cell);
	//	}
	//	cells.push_back(row);
	//}
}

void SceneMapTool::ClearCellsByCategory(const Category& cate)
{
	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.RemoveAllGameObjectByCategory(cate);
		}
	}
}

void SceneMapTool::Init()
{
	Scene::Init();
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	
	//윈도우 가운데로
	FRAMEWORK.GetWindow().setPosition(sf::Vector2i((1920 - windowSize.x * 4.f) / 2, (1080 - windowSize.y * 4.f) / 2));

	originalSize = { 24 * 20, 24 * 20 };
	mapSize = originalSize;
	TextGameObj* layerText = (TextGameObj*)AddGameObject(new TextGameObj("fonts/D2Coding.ttc", 20, "Layer"));
	layerText->text.setScale({0.3f, 0.3f});
	layerText->SetFillColor(sf::Color::Magenta);
	layerText->sortLayer = paletteLayer - 1;
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
	
	
	for (int i = 0; i < (windowSize.y / cellSize.y) + 2; i++)
	{
		for (int j = 0; j < (windowSize.x / cellSize.x) + 2; j++)
		{
			RectangleShapeGO* grid = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("gird"));
			grid->SetSize(cellSize);
			grid->SetOrigin(Origins::TL);
			grid->SetOutlineThickness(0.2f);
			grid->SetFillColor(sf::Color::Transparent);
			grid->SetOutlineColor(sf::Color::White);
			grid->SetPosition({ j * cellSize.x, i * cellSize.y });
			grid->sortLayer = UILayer;
			grids.push_back(grid);
		}
	}

	auto size = FRAMEWORK.GetWindowSize();
	menuBase = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("MenuBase"));
	menuBase->SetSize({ size.x * 0.3f, size.y });
	menuBase->SetFillColor(sf::Color(72, 72, 72));
	menuBase->sortLayer = UILayer;
	menuBase->SetOrigin(Origins::TL);
	menuBase->SetPosition({ size.x * 0.7f, 0.f });

}

void SceneMapTool::Update(float dt)
{
	Scene::Update(dt);
	sf::Vector2f viewportPos = worldView.getCenter() - worldView.getSize() * 0.5f ;
	sf::Vector2f cellOrigin = { (float)((int)viewportPos.x % (int)cellSize.x), (float)((int)viewportPos.y % (int)cellSize.y) };
	//for (auto& row : cells)
	//{
	//	for (auto& col : row)
	//	{
	//		col.SetOrigin(cellOrigin);
	//	}
	//}
	for (auto grid : grids)
	{
		grid->SetOrigin(cellOrigin);
	}

	//Move
	if (Input.GetKey(sf::Keyboard::W) && worldView.getCenter().y - (worldView.getSize().y * 0.5f) > 0.0f)
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y - uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::S) && worldView.getCenter().y + (worldView.getSize().y * 0.5f) < mapSize.y)
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y + uiSpeed * dt);
	}
	if (Input.GetKey(sf::Keyboard::A) && worldView.getCenter().x - (worldView.getSize().x * 0.5f) > 0.0f)
	{
		worldView.setCenter(worldView.getCenter().x - uiSpeed * dt, worldView.getCenter().y);
	}
	if (Input.GetKey(sf::Keyboard::D) && worldView.getCenter().x + (worldView.getSize().x * 0.5f) < mapSize.x + menuBase->GetSize().x)
	{
		worldView.setCenter(worldView.getCenter().x + uiSpeed * dt, worldView.getCenter().y);
	}
	//paletteMove
	if (Input.GetMouseScrollDelta() != 0)
	{
		if (Input.GetMouseScrollDelta(true) < 0 && palettes[0]->GetPosition().y > menuBase->GetSize().y * 0.2f)
		{
			return;
		}
		for (auto palette : palettes)
		{
			palette->SetPosition(palette->GetPosition().x, palette->GetPosition().y - Input.GetMouseScrollDelta(true) * scrollForce);
			if (palette->GetPosition().y < menuBase->GetSize().y * 0.2f)
			{
				palette->SetActive(false);
			}
			else
			{
				palette->SetActive(true);
			}
		}
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

	auto cell = GetCell(ScreenToWorldPosition(Input.GetMousePosition()));
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
			if (currentGO->GetCategory() != Category::Door && currentGO->GetCategory() != Category::Camera)
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
			else if (currentGO->GetCategory() == Category::Camera)
			{
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
			else if(currentGO->GetCategory() == Category::Camera)
			{
				prevGO->additionalData["EndPosition"]["x"] = currentGO->GetPosition().x;
				prevGO->additionalData["EndPosition"]["y"] = currentGO->GetPosition().y;
				//auto go = cell->AddGameObject(currentGO, layer);
				//go->additionalData["Type"] = (int)CameraType::MapEnd;
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

	//Flip
	if (Input.GetKeyDown(sf::Keyboard::Space))
	{
		currentGO->SetFlipX(flipX);
		flipX = !flipX;
		currentGO->additionalData["FlipX"] = flipX;
		std::cout << currentGO->sprite.getOrigin().x
			<< " " <<
		currentGO->sprite.getOrigin().y << std::endl;
		currentGO->SetOrigin({ (flipX) ? 24.0f : 0.f, 0.f});
		if (!currentGO->additionalData["Angle"].isNull())
		{
			currentGO->additionalData["Angle"] = currentGO->additionalData["Angle"].asFloat() * -1;
		}
	}

	if (Input.GetKeyDown(Keyboard::F11))
	{
		SCENE_MANAGER.ChangeScene(SceneId::Title);
	}
}

void SceneMapTool::Draw(sf::RenderWindow& window)
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

	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.Draw(window);
		}
	}
	window.setView(uiView);


	for (auto go : gameObjects)
	{
		if (go->sortLayer < UILayer || go->sortLayer > paletteLayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}

	window.setView(paletteView);
	for (auto go : gameObjects)
	{
		if (go->sortLayer < paletteLayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}
}

void SceneMapTool::Release()
{
}

void SceneMapTool::Reset()
{
	for (auto& row : cells)
	{
		for (auto& col : row)
		{
			col.RemoveAllGameObject();
		}
	}
	cells.clear();
	
	mapSize = originalSize;
	cellHorizontalCount = floor(mapSize.x / cellSize.x);
	cellVerticalCount = floor(mapSize.y / cellSize.y);
	for (int i = 0; i < cellVerticalCount; i++)
	{
		std::vector<MapToolCell> row;
		for (int j = 0; j < cellHorizontalCount; j++)
		{
			MapToolCell cell;
			cell.SetSize(cellSize);
			cell.SetPosition({ j * cellSize.x, i * cellSize.y });
			row.push_back(cell);
		}
		cells.push_back(row);
	}

	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneMapTool::Exit()
{
	Scene::Exit();
}

void SceneMapTool::SaveData(const std::wstring& path)
{
	if (path == "")
	{
		return;
	}
	Json::Value rootNode;
	rootNode["Stage"] = (int)stageIndex;
	rootNode["Path"] = mapPath;
	rootNode["MapSize"]["x"] = mapSize.x;
	rootNode["MapSize"]["y"] = mapSize.y;

	Json::Value playerNode;
	Json::Value itemNodes;
	Json::Value enemyNodes;
	Json::Value doorNodes;
	Json::Value groundNodes;
	Json::Value cameraNodes;
	Json::Value ambientObjectNodes;

	for (int i = 0; i < cells.size(); i++)
	{
		auto row = cells[cells.size() - ( i + 1)];
	//}
	//for (auto& row : cells)
	//{
		for (int j = 0; j < row.size(); j++)
		{
			auto col = row[row.size() - (j + 1)];
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
				node["FlipX"] = ((SpriteGO*)go)->additionalData["FlipX"].asBool();

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
					node["Type"] = ((SpriteGO*)go)->additionalData["Type"].asInt();
					node["TexturePosition"]["x"] = ((SpriteGO*)go)->additionalData["Position"]["x"].asFloat();
					node["TexturePosition"]["y"] = ((SpriteGO*)go)->additionalData["Position"]["y"].asFloat();
					if ((GroundType)((SpriteGO*)go)->additionalData["Type"].asInt() == GroundType::Tilted)
					{
						node["Angle"] = ((SpriteGO*)go)->additionalData["Angle"].asFloat();
						node["OffSet"]["x"] = ((SpriteGO*)go)->additionalData["OffSet"]["x"].asFloat();
						node["OffSet"]["y"] = ((SpriteGO*)go)->additionalData["OffSet"]["y"].asFloat();
					}
					groundNodes.append(node);
					break;
				case Category::Camera:
					node["Type"] = ((SpriteGO*)go)->additionalData["Type"].asInt();
					node["EndPosition"]["x"] = ((SpriteGO*)go)->additionalData["EndPosition"]["x"].asFloat();
					node["EndPosition"]["y"] = ((SpriteGO*)go)->additionalData["EndPosition"]["y"].asFloat();
					cameraNodes.append(node);
					break;
				case Category::AmbientObject:
					ambientObjectNodes.append(node);
					break;
				}
			}
		}
	}

	std::vector<Json::Value> sortArray;
	for (int i = 0; i < groundNodes.size(); i++)
	{
		sortArray.push_back(groundNodes[i]);
	}
	groundNodes.clear();
	std::sort(sortArray.begin(), sortArray.end(), [](Json::Value& a, Json::Value& b) {
		float aY = a["Position"]["y"].asFloat();
		float bY = b["Position"]["y"].asFloat();
		if (!a["OffSet"]["y"].isNull())
		{
			aY += a["OffSet"]["y"].asFloat();
		}
		if (!b["OffSet"]["y"].isNull())
		{
			bY += b["OffSet"]["y"].asFloat();
		}

		return aY > bY;
	});
	for (auto& ground : sortArray)
	{
		groundNodes.append(ground);
	}

	rootNode["Player"] = playerNode;
	rootNode["Item"] = itemNodes;
	rootNode["Enemy"] = enemyNodes;
	rootNode["Door"] = doorNodes;
	rootNode["Ground"] = groundNodes;
	rootNode["Camera"] = cameraNodes;
	rootNode["AmbientObject"] = ambientObjectNodes;

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, rootNode);
	
	std::ofstream ofile(path);

	if (ofile.is_open()) {
		ofile << json_file;
		ofile.close();
	}
}

void SceneMapTool::LoadData(const std::wstring& path)
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

	Reset();
	int AddColumnCount = floor(rootNode["MapSize"]["x"].asInt() - mapSize.x) / cellSize.x;
	int AddRowCount = floor(rootNode["MapSize"]["y"].asInt() - mapSize.y) / cellSize.y;
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
		player->SetFlipX(playerNode["FlipX"].isBool());
		player->sprite.setScale({1.f, 1.f});
		player->SetPosition(loadPosition);
		cell = GetCell(loadPosition);
		cell->AddGameObject(player, playerNode["SortLayer"].asInt());
	}

	for (int i = 0; i < itemNodes.size(); i++)
	{
		Json::Value node = itemNodes[i];
		Item* go = (Item*)CopyUIButton(node["PaletteID"].asString());
		loadPosition = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		go->SetItemType((ItemType)node["Type"].asInt());
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, node["SortLayer"].asInt());
	}

	for (int i = 0; i < enemyNodes.size(); i++)
	{
		Json::Value node = enemyNodes[i];
		Enemy* go = (Enemy*)CopyUIButton(node["PaletteID"].asString());
		loadPosition = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		go->SetEnemyType((EnemyType)node["Type"].asInt());
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, node["SortLayer"].asInt());
	}

	for (int i = 0; i < doorNodes.size(); i++)
	{
		Json::Value node = doorNodes[i];
		SpriteGO* go = CopyUIButton(node["PaletteID"].asString());
		loadPosition = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		go->additionalData["MovePosition"]["x"] = node["MovePosition"]["x"];
		go->additionalData["MovePosition"]["y"] = node["MovePosition"]["y"];
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, node["SortLayer"].asInt());
	}

	for (int i = 0; i < groundNodes.size(); i++)
	{
		Json::Value node = groundNodes[i];
		Ground* go = (Ground*)CopyUIButton(node["PaletteID"].asString());
		loadPosition = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		go->SetFlipX(node["FlipX"].isBool());
		go->SetGroundIndex(node["GroundIndex"].asInt());
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, node["SortLayer"].asInt());
	}

	for (int i = 0; i < ambientObjectNodes.size(); i++)
	{
		Json::Value node = ambientObjectNodes[i];
		AmbientObject* go = (AmbientObject*)CopyUIButton(node["PaletteID"].asString());
		loadPosition = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		go->sprite.setScale({ 1.f, 1.f });
		go->SetPosition(loadPosition);
		cell = GetCell(loadPosition);
		cell->AddGameObject(go, node["SortLayer"].asInt());
	}
}
const std::wstring SceneMapTool::GetLoadFilePathWithOpenWindow()
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

const std::wstring SceneMapTool::GetSaveFilePathWithOpenWindow()
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

Json::Value SceneMapTool::LoadFromJsonFile(const std::string& path)
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

SpriteGO* SceneMapTool::CopyUIButton(const std::string& paletteID)
{
	SpriteGO* findGo = (SpriteGO*)FindGameObject(paletteID);
	if (findGo == nullptr)
	{
		return nullptr;
	}
	SpriteGO* instance = new SpriteGO(*findGo);

	return instance;
}

void SceneMapTool::SetLayer(int layer)
{
	this->layer = layer;
	TextGameObj* findGo = (TextGameObj*)FindGameObject("Layer");
	std::stringstream ss;
	ss << "Layer: " << this->layer;
	if (drawCurrentLayerOnly)
	{
		ss << " Only";
	}
	findGo->SetString(ss.str());
}

void SceneMapTool::ReSizeMap(bool expand)
{
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
}

void SceneMapTool::AddColumn()
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
void SceneMapTool::DelColumn()
{
	// 열 제거
	for (int i = 0; i < cellVerticalCount; i++)
	{
		cells[i][cellHorizontalCount - 1].RemoveAllGameObject();
		cells[i].pop_back();
	}
	cellHorizontalCount--;
	mapSize.x -= (int)cellSize.x;
}
void SceneMapTool::AddRow()
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
void SceneMapTool::DelRow()
{
	// 행 제거
	for (auto& cell : cells[cellVerticalCount - 1])
	{
		cell.RemoveAllGameObject();
	}
	cells.pop_back();
	cellVerticalCount--;
	mapSize.y -= (int)cellSize.y;
}

sf::Vector2f SceneMapTool::ScreenToPalettePosition(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, paletteView);
}
sf::Vector2f SceneMapTool::PalettePositionToScreen(sf::Vector2f palettePos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(palettePos, paletteView);
}