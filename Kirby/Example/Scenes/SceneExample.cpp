#include "stdafx.h"
#include <Framework.h>
#include "SceneExample.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SoundGO.h"
#include <SpriteGO.h>
#include "TextGameObj.h"
#include <DataTableManager.h>
#include <StringTable.h>
#include <RectangleShapeGO.h>
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include <UIButton.h>
#include <SpriteTextGO.h>
#include <AnimatorPlayer.h>
#include <AudioSource.h>
#include <GameObjects/CircleShapeGO.h>
#include <Components/Physics/CircleCollider.h>

SceneExample::SceneExample() 
	: Scene(SceneId::Title)
{
	sceneName = "TitleScene";
}

SceneExample::~SceneExample()
{
	Release();
}

void SceneExample::Enter()
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

void SceneExample::Reset()
{

	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneExample::Exit()
{
	Scene::Exit();
}

void SceneExample::Init()
{
	Scene::Init();
	Release();

	RectangleShapeGO* rectGO = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO());
	rectGO->SetSize({ 40.0f, 40.0f });
	rectGO->SetOrigin(Origins::BR);
	BoxCollider* boxCol = (BoxCollider*)rectGO->AddComponent(new BoxCollider(*rectGO));

	CircleShapeGO* circleGO = (CircleShapeGO*)AddGameObject(new CircleShapeGO());
	circleGO->SetSize({ 40.0f, 40.0f });
	circleGO->SetOrigin(Origins::TL);
	CircleCollider* circleCol = (CircleCollider*)circleGO->AddComponent(new CircleCollider(*circleGO));
	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneExample::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneExample::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SceneExample::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
