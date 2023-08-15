#include "stdafx.h"
#include "Framework.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "json.h"

#include "RectangleShapeGO.h"

GameScene::GameScene()
	: Scene(SceneId::Game)
{
	sceneName = "GameScene";
}

GameScene::~GameScene()
{
	Release();
}

void GameScene::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	auto screenCenter = size * 0.5f;
	worldView.setSize(size);
	worldView.setCenter(0.0f, 0.0f);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	Scene::Enter();

	Reset();
}

void GameScene::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void GameScene::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void GameScene::Init()
{
	Scene::Init();
	Release();

	RectangleShapeGO* go = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Temp"));
	go->SetSize({ 24.f, 24.f });

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void GameScene::Update(float dt)
{
	
}

void GameScene::Draw(sf::RenderWindow& window)
{
}
