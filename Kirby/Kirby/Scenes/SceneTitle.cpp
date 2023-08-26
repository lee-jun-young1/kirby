#include "stdafx.h"
#include "SceneTitle.h"
#include "GameObject.h"
#include "Framework.h"
#include "InputManager.h"
#include "SpriteGO.h"
#include "DataSlot.h"
SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	sceneName = "TitleScene";
}
SceneTitle::~SceneTitle()
{
	Release();
}
void SceneTitle::Enter()
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
void SceneTitle::Reset()
{
	SpriteGO* title = (SpriteGO*)FindGameObject("Title");
	DataSlot* save1 = (DataSlot*)FindGameObject("Save1");
	DataSlot* save2 = (DataSlot*)FindGameObject("Save2");
	DataSlot* save3 = (DataSlot*)FindGameObject("Save3");

	title->SetPosition(0, 0);
	save1->SetPosition(0, save1->sprite.getGlobalBounds().height * -1.0f);
	save2->SetPosition(save1->sprite.getGlobalBounds().left + save1->sprite.getGlobalBounds().width, save2->sprite.getGlobalBounds().height);
	save3->SetPosition(save2->sprite.getGlobalBounds().left + save2->sprite.getGlobalBounds().width, save3->sprite.getGlobalBounds().height * -1.0f);
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Init()
{
	Scene::Init();
	Release();

	SpriteGO* title = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/Title/Title.png", "Title"));
	DataSlot* save1 = (DataSlot*)AddGameObject(new DataSlot("sprites/UI/Title/Save1.png", "Save1"));
	save1->SetMoveDirection(DataSlot::Direction::Down);
	DataSlot* save2 = (DataSlot*)AddGameObject(new DataSlot("sprites/UI/Title/Save2.png", "Save2"));
	save2->SetMoveDirection(DataSlot::Direction::Up);
	DataSlot* save3 = (DataSlot*)AddGameObject(new DataSlot("sprites/UI/Title/Save3.png", "Save3"));
	save3->SetMoveDirection(DataSlot::Direction::Down);

}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneTitle::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if (Input.GetKeyDown(sf::Keyboard::Enter))
	{
		DataSlot* save1 = (DataSlot*)FindGameObject("Save1");
		DataSlot* save2 = (DataSlot*)FindGameObject("Save2");
		DataSlot* save3 = (DataSlot*)FindGameObject("Save3");
		save1->SetMoveActive(true);
		save2->SetMoveActive(true);
		save3->SetMoveActive(true);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

