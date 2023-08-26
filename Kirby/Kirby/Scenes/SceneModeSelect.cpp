#include "stdafx.h"
#include "SceneModeSelect.h"
#include "GameObject.h"
#include "Framework.h"
#include "InputManager.h"
#include "SpriteGO.h"
#include "ModeButton.h"
#include "SceneManager.h"
#include "ModeSelectBoard.h"

SceneModeSelect::SceneModeSelect() : Scene(SceneId::ModeSelect)
{
	sceneName = "ModeSelectScene";
}
SceneModeSelect::~SceneModeSelect()
{
	Release();
}
void SceneModeSelect::Enter()
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
void SceneModeSelect::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
	auto size = FRAMEWORK.GetWindowSize();

	ModeSelectBoard* board = (ModeSelectBoard*)FindGameObject("Board");
	board->SetPosition({ (size.x - (board->sprite.getGlobalBounds().left + board->sprite.getGlobalBounds().width)) * 0.5f, size.y * 0.02f });
	SpriteGO* logo = (SpriteGO*)FindGameObject("Logo");
	logo->SetPosition(board->GetPosition().x, board->sprite.getGlobalBounds().top + board->sprite.getGlobalBounds().height + 2.0f);

}

void SceneModeSelect::Exit()
{
	Scene::Exit();
}

void SceneModeSelect::Init()
{
	Scene::Init();
	Release();

	ModeSelectBoard* board = (ModeSelectBoard*)AddGameObject(new ModeSelectBoard("sprites/UI/ModeSelect/Board.png", "Board"));
	board->sortLayer = 0;

	SpriteGO* logo = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Logo.png", "Logo"));

	ModeButton* mode = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/SpringBreeze.png", "Mode"));
	mode->SetPosition( 24.0f, 16.0f);
	mode->sortLayer = 1;
	mode->SetNextSceneID(SceneId::SpringBreeze);
	SpriteGO* guide = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/SpringBreezeGuide.png", "Guide"));
	guide->SetPosition({ 10.0f, 10.0f });
	mode->SetGuide(guide);
	board->AddMode(mode);

	//ModeButton* mode1 = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/SpringBreeze.png", "Mode"));
	//mode1->SetPosition(48.0f, 96.0f);
	//mode1->sortLayer = 1;
	//SpriteGO* guide1 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/SpringBreezeGuide.png", "Guide"));
	//guide1->SetPosition({ 10.0f, 10.0f });
	//mode1->SetGuide(guide1);
	//board->AddMode(mode1);
}

void SceneModeSelect::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneModeSelect::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SceneModeSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}