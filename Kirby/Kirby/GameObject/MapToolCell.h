#pragma once
#include "RectangleShapeGO.h"
class SpriteGO;
class MapToolCell : public RectangleShapeGO
{
protected:
	std::list<GameObject*> gameObjects;

public:
	MapToolCell(const string& name = "");
	virtual ~MapToolCell() override;
	
	const std::list<GameObject*>& GetGameObjects() const { return gameObjects; }

	void AddGameObject(RectangleShapeGO* gameObject, int layer);
	void AddGameObject(SpriteGO* gameObject, int layer);
	void RemoveGameObject(int layer);
	void RemoveAllGameObject();
	void RemoveAllGameObjectByName(const std::string& name);

	virtual void Draw(sf::RenderWindow& window) override;
	void DrawGameObject(sf::RenderWindow& window, const int& layer, const bool& drawCurrentLayerOnly = false);
};

