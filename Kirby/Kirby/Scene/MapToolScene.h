#pragma once
#include "Scene.h"
#include "json.h"
class MapToolScene : public Scene
{
protected:
	StageIndex stageIndex;
	std::string currentFileName;

	std::vector<sf::RectangleShape> cells;
public:
	

	void SaveData();
	void LoadData(const std::string& fileName);

	virtual void Init() override;
	virtual void Draw(sf::RenderWindow& window) override;
};

