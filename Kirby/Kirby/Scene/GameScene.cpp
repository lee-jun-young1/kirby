#include "stdafx.h"
#include "Framework.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "json.h"
#include "Utils.h"

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

	auto size = FRAMEWORK.GetWindowSize();
	VertexArrayGO* background = CreateBackground({ 1, 1 }, size);
	AddGameObject(background);
	background->SetOrigin(Origins::MC);
	background->SetPosition(0.f, 0.f);
	background->sortLayer = -99;
	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void GameScene::Update(float dt)
{
	movement = { Input.GetAxisRaw(Axis::Horizontal), Input.GetAxisRaw(Axis::Vertical) };
	worldView.setCenter(worldView.getCenter() + movement * 50.f * dt);

	//worldView.setCenter();
}

void GameScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

VertexArrayGO* GameScene::CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize, const std::string& textureId)
{
	VertexArrayGO* background = new VertexArrayGO(textureId, "bg");
	sf::Vector2f startPos = { 0,0 };

	
	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray.resize(tileMatrix.x * tileMatrix.y * 4);

	sf::Vector2f offsets[4] =
	{
		{0.f,0.f},
		{tileSize.x,0.f},
		{tileSize.x,tileSize.y },
		{0.f,tileSize.y}
	};

	sf::Vector2f texOffsets[4] =
	{
		{0.f,0.f},
		{texSize.x,0.f},
		{texSize.x,texSize.y },
		{0.f,texSize.y}
	};

	sf::Vector2f currPos = startPos;
	for (int i = 0; i < tileMatrix.y; ++i)
	{
		for (int j = 0; j < tileMatrix.x; ++j)
		{
			int tileIndex = tileMatrix.x * i + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = tileIndex * 4 + k;
				sf::Color color = (vertexIndex < 2) ? sf::Color::White : sf::Color::Black;
				background->vertexArray[vertexIndex].position = currPos + offsets[k];
				background->vertexArray[vertexIndex].color = color;
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
	return background;
}