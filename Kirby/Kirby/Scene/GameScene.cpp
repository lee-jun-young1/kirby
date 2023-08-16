#include "stdafx.h"
#include "Framework.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "json.h"

//test
#include "VertexArrayGO.h"

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

	VertexArrayGO* background = (VertexArrayGO*)AddGameObject(new VertexArrayGO("", "bg"));
	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray.resize(4);
	
	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void GameScene::Update(float dt)
{
	
	//worldView.setCenter();
}

void GameScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
