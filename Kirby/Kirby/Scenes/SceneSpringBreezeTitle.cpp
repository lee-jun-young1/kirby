#include "stdafx.h"
#include "SceneSpringBreezeTitle.h"
#include "GameObject.h"
#include "Framework.h"
#include "InputManager.h"
#include "SpriteGO.h"
#include "DataSlot.h"
#include "SceneManager.h"
SceneSpringBreezeTitle::SceneSpringBreezeTitle() : Scene(SceneId::SpringBreeze)
{
	sceneName = "SpringBreezeTitleScene";
}
SceneSpringBreezeTitle::~SceneSpringBreezeTitle()
{
	Release();
}
void SceneSpringBreezeTitle::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	auto screenCenter = size * 0.5f;

	worldView.setSize(size);
	worldView.setCenter(screenCenter);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	Scene::Enter();
	Reset();
}
void SceneSpringBreezeTitle::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneSpringBreezeTitle::Exit()
{
	Scene::Exit();
}

void SceneSpringBreezeTitle::Init()
{
	Scene::Init();
	Release();
	
	auto size = FRAMEWORK.GetWindowSize();
	SpriteGO* title = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/SpringBreeze/SpringBreezeTitle.png", "Title"));
	SpriteGO* button = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/SpringBreeze/NewGame.png", "Button"));
	button->SetOrigin(Origins::MC);
	button->SetPosition(72.0f, 144.0);
}

void SceneSpringBreezeTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneSpringBreezeTitle::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if (Input.GetKeyDown(sf::Keyboard::X))
	{
		SCENE_MANAGER.ChangeScene(SceneId::Game);
	}
}

void SceneSpringBreezeTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}