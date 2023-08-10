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
	RectangleShapeGO* instance = new RectangleShapeGO();
	instance->SetSize(gameObject->GetSize());
	instance->SetFillColor(gameObject->GetFillColor());
	instance->sortLayer = layer;
	instance->SetActive(true);
	instance->SetOrigin(gameObject->GetOrigin());
	instance->SetPosition(gameObject->GetPosition());
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

void MapToolCell::AddGameObject(SpriteGO* gameObject, int layer)
{
	if (gameObject == nullptr)
	{
		return;
	}
	SpriteGO* instance = new SpriteGO(*gameObject);
	instance->sortLayer = layer;
	std::cout
		<< "Name: " << instance->GetName()
		<< " PositionX: " << instance->GetPosition().x
		<< " PositionY: " << instance->GetPosition().y
		<< " layer: " << instance->sortLayer
		<< std::endl;
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

void MapToolCell::RemoveAllGameObjectByName(const std::string& name)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->GetName() == name)
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
	RectangleShapeGO::Draw(window);
}

void MapToolCell::DrawGameObject(sf::RenderWindow& window,const int& layer, const bool& drawCurrentLayerOnly)
{
	for (auto go : gameObjects)
	{
		if (!(drawCurrentLayerOnly && layer == go->sortLayer))
		{
			go->Draw(window);
		}
	}
}
