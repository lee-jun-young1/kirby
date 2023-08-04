#pragma once
#include "Scene.h"
#include "json.h"
class MapToolScene : public Scene
{
protected:
	StageIndex stageIndex;
	std::string currentFileName;

	std::vector<sf::RectangleShape> cells;
	sf::Vector2f cellSize = {24.0f, 24.0f};

	int cellHorizontalCount;
	int cellVerticalCount;
public:
	MapToolScene();
	~MapToolScene();

	void SaveData();
	void LoadData(const std::string& fileName);

	virtual void Enter() override;

	// Scene을(를) 통해 상속됨
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

