#pragma once
#include "Scene.h"
#include "json.h"
#include "MapToolCell.h"

class SpriteGO;
class MapToolScene : public Scene
{
protected:
	StageIndex stageIndex;

	std::vector<MapToolCell> cells;
	sf::Vector2f cellSize = { 24.0f, 24.0f };
	int cellHorizontalCount;
	int cellVerticalCount;

	sf::Vector2i mapSize;
	RectangleShapeGO* currentGameObject = nullptr;
	SpriteGO* currentGO = nullptr;

	sf::Vector2f worldMovement;
	float uiSpeed = 50.f;

	int layer = 0;
	bool drawCurrentLayerOnly = false;
public:
	MapToolScene();
	~MapToolScene();

	MapToolCell* GetCell(const sf::Vector2f& position);
	void SelectGameObject(RectangleShapeGO* gameObject);
	void SelectGameObject(SpriteGO* gameObject);

	virtual void Enter() override;

	// Scene을(를) 통해 상속됨
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SaveData(const std::wstring& path);
	void LoadData(const std::wstring& path);

	const std::wstring GetFilePathWithOpenWindow();
	const std::wstring GetSaveFileNameWithOpenWindow();

	Json::Value LoadFromJsonFile(const std::string& path);
	SpriteGO* CopyUIButton(const std::string& name);
	void SetLayer(int layer);
};

