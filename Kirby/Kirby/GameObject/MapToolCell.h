#pragma once
#include "RectangleShapeGO.h"
class SpriteGO;
class Player;
class Item;
class Enemy;
class Ground;
class Door;
class AmbientObject;
class MapToolCell : public RectangleShapeGO
{
protected:
	std::list<GameObject*> gameObjects;

public:
	MapToolCell(const string& name = "");
	virtual ~MapToolCell() override;
	
	const std::list<GameObject*>& GetGameObjects() const { return gameObjects; }

	void AddGameObject(RectangleShapeGO* gameObject, int layer);
	//void AddGameObject(SpriteGO* gameObject, int layer);
	SpriteGO* AddGameObject(SpriteGO* gameObject, int layer);

	void RemoveGameObject(int layer);
	void RemoveAllGameObject();
	void RemoveAllGameObjectByCategory(const Category& cate);

	virtual void Draw(sf::RenderWindow& window) override;
	void DrawGameObject(sf::RenderWindow& window, const int& layer, const bool& drawCurrentLayerOnly = false);
};

