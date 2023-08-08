#pragma once
#include "Scene.h"
#include "json.h"
#include "MapToolCell.h"

class MapToolScene : public Scene
{
protected:
	StageIndex stageIndex;
	std::string currentFileName;

	std::vector<MapToolCell> cells;
	sf::Vector2f cellSize = {24.0f, 24.0f};
	int cellHorizontalCount;
	int cellVerticalCount;

	sf::Vector2f mapSize;
	RectangleShapeGO* currentGameObject = nullptr;

	sf::Vector2f worldMovement;
	float uiSpeed = 50.f;

	int layer = 0;
	bool drawCurrentLayerOnly = false;
public:
	MapToolScene();
	~MapToolScene();

	void SaveData();
	void LoadData(const std::string& fileName);

	MapToolCell* GetCell(const sf::Vector2f& position);
	void SelectGameObject(RectangleShapeGO* gameObject);

	virtual void Enter() override;

	// Scene을(를) 통해 상속됨
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

