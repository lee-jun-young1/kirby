#include "stdafx.h"
#include "MapToolCell.h"
#include "SpriteGO.h"
MapToolCell::MapToolCell(const string& name)
	:RectangleShapeGO(name)
{
}

MapToolCell::~MapToolCell()
{
}

void MapToolCell::AddGameObject(RectangleShapeGO* gameObject, int layer)
{
	if (gameObject == nullptr)
	{
		return;
	}
	RectangleShapeGO* instance = new RectangleShapeGO(*gameObject);
	instance->sortLayer = layer;
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->sortLayer == instance->sortLayer)
		{
			delete *it;
			it = gameObjects.erase(it);
		}
		else
		{
			it++;
		}
	}

	gameObjects.push_back(instance);
}

SpriteGO* MapToolCell::AddGameObject(SpriteGO* gameObject, int layer)
{
	if (gameObject == nullptr)
	{
		return nullptr;
	}
	SpriteGO* instance = new SpriteGO(*gameObject);
	instance->sprite.setColor(sf::Color(255, 255, 255, 255));
	instance->sortLayer = layer;
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->sortLayer == instance->sortLayer)
		{
			delete* it;
			it = gameObjects.erase(it);
		}
		else
		{
			it++;
		}
	}

	gameObjects.push_back(instance);
	return instance;
}

void MapToolCell::RemoveGameObject(int layer)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->sortLayer == layer)
		{
			delete *it;
			it = gameObjects.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void MapToolCell::RemoveAllGameObject()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		delete* it;
		it = gameObjects.erase(it);
	}
}

void MapToolCell::RemoveAllGameObjectByCategory(const Category& cate)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->GetCategory() == cate)
		{
			delete* it;
			it = gameObjects.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void MapToolCell::Draw(sf::RenderWindow& window)
{
}

void MapToolCell::DrawGameObject(sf::RenderWindow& window,const int& layer, const bool& drawCurrentLayerOnly)
{
	gameObjects.sort([](GameObject* lhs, GameObject* rhs) {
		if (lhs->sortLayer != rhs->sortLayer)
		{
			return lhs->sortLayer < rhs->sortLayer;
		}
		return lhs->sortOrder < rhs->sortOrder;
		});
	for (auto go : gameObjects)
	{
		if (!(drawCurrentLayerOnly && layer == go->sortLayer))
		{
			go->Draw(window);
		}
	}
}
