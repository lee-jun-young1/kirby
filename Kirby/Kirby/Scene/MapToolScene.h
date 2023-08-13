#pragma once
#include "Scene.h"
#include "json.h"
#include "MapToolCell.h"

class SpriteGO;
class Door;
class MapToolScene : public Scene
{
protected:
	StageIndex stageIndex;

	std::vector<std::vector<MapToolCell>> cells;
	sf::Vector2f cellSize = { 24.0f, 24.0f };
	int cellHorizontalCount;
	int cellVerticalCount;

	sf::Vector2i originalSize;
	sf::Vector2i mapSize;
	SpriteGO* currentGO = nullptr;

	float uiSpeed = 200.f;

	RectangleShapeGO* menuBase;
	sf::Vector2f paletteSpace = { 1.f, 1.f };
	sf::Vector2f paletteScale = { 0.5f, 0.5f };

	int layer = 0;
	bool drawCurrentLayerOnly = false;

	//temp
	SpriteGO* prevGO = nullptr;
	sf::Vector2f doorMovePosition;

public:
	MapToolScene();
	~MapToolScene();

	MapToolCell* GetCell(const sf::Vector2f& position);
	void SelectGameObject(SpriteGO* gameObject);

	void ClearCells();
	void ClearCellsByCategory(const Category& cate);

	virtual void Enter() override;

	// Scene을(를) 통해 상속됨
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SaveData(const std::wstring& path);
	void LoadData(const std::wstring& path);

	const std::wstring GetLoadFilePathWithOpenWindow();
	const std::wstring GetSaveFilePathWithOpenWindow();

	Json::Value LoadFromJsonFile(const std::string& path);
	SpriteGO* CopyUIButton(const std::string& name);
	void SetLayer(int layer);
	void ReSizeMap(bool expand);

	void AddColumn();
	void DelColumn();
	void AddRow();
	void DelRow();
};

