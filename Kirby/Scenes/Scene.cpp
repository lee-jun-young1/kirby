#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Framework.h"
#include <rapidcsv.h>

Scene::Scene(SceneId id)
	:sceneId(id), window(FRAMEWORK.GetWindow())
{
}

Scene::~Scene()
{
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	auto compare = [name](GameObject* go) {return go->GetName() == name; };
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(), compare);
	if (it == gameObjects.end())
	{
		return nullptr;
	}
	return *it;
	/*
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			return go;
		}
	}
	return nullptr;
	*/
}

void Scene::FindGameObjects(std::list<GameObject*>& list, const std::string& name)
{
	//list.clear();
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			list.push_back(go);
		}
	}
}

bool Scene::Exist(GameObject* gameObject)
{
	return std::find(gameObjects.begin(), gameObjects.end(), gameObject) != gameObjects.end();
}

GameObject* Scene::AddGameObject(GameObject* gameObject)
{
	if (!Exist(gameObject))
	{
		gameObjects.push_back(gameObject);
	}
	return gameObject;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	removeGameObjects.push_back(gameObject);
	//gameObjects.remove(gameObject);
	//delete gameObject;
}

void Scene::SortGameObjects()
{
	gameObjects.sort([](GameObject* lhs, GameObject* rhs) {
		if (lhs->sortLayer != rhs->sortLayer)
		{
			return lhs->sortLayer < rhs->sortLayer;
		}
		return lhs->sortOrder < rhs->sortOrder;
		});
}

sf::Vector2f Scene::ScreenToWorldPosition(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, worldView);
}

sf::Vector2f Scene::ScreenToUIPosition(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, uiView);
}

sf::Vector2f Scene::WorldPositionToScreen(sf::Vector2f worldPos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::UIPositionToScreen(sf::Vector2f uiPos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(uiPos, uiView);
}

void Scene::Enter()
{
	Resources.Load(resources);

	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void Scene::Exit()
{
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();

	Resources.Unload(resources);
}

void Scene::Init()
{
	rapidcsv::Document doc("data/" + sceneName + "_resources.csv");
	std::vector<int> types = doc.GetColumn<int>(0);
	std::vector<std::string> paths = doc.GetColumn<std::string>(1);
	std::cout << "===" + sceneName + "===" << std::endl;
	for (int i = 0; i < types.size(); ++i)
	{
		std::cout << types[i] << ", " << paths[i] << std::endl;
		resources.push_back(std::make_tuple((ResourceTypes)types[i], paths[i]));
	}
	std::cout << "===" + sceneName + "===" << std::endl;
}


void Scene::UpdateComponent(float deltaTime)
{
	for (auto go : gameObjects)
	{
		if (go->IsActive())
		{
			go->UpdateComponent(deltaTime);
		}
	}
}


void Scene::Update(float deltaTime)
{
	for (auto go : gameObjects)
	{
		if (go->IsActive())
		{
			go->Update(deltaTime);
		}
	}

	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

void Scene::Draw(sf::RenderWindow& window)
{
	SortGameObjects();

	window.setView(worldView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer >= UILayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}


	window.setView(uiView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer < UILayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}
}

void Scene::OnGUI(sf::RenderWindow& window)
{
	window.setView(worldView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer >= UILayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->OnGUI(window);
		}
	}


	window.setView(uiView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer < UILayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->OnGUI(window);
		}
	}
}