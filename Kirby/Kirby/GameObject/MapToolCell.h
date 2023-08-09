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
	
	void AddGameObject(RectangleShapeGO* gameObject, int layer);
	void AddGameObject(SpriteGO* gameObject, int layer);
	void RemoveGameObject(int layer);

	virtual void Draw(sf::RenderWindow& window) override;
	void DrawGameObject(sf::RenderWindow& window, const int& layer, const bool& drawCurrentLayerOnly = false);
};

