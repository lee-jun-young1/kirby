#include "stdafx.h"
#include "SceneModeSelect.h"
#include "GameObject.h"
#include "Framework.h"
#include "InputManager.h"
#include "SpriteGO.h"
#include "ModeButton.h"
#include "SceneManager.h"

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
}

void SceneModeSelect::Exit()
{
	Scene::Exit();
}

void SceneModeSelect::Init()
{
	Scene::Init();
	Release();

	SpriteGO* board = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/BoardWithLogo.png", "Board"));
	board->sortLayer = -1;
	ModeButton* mode = (ModeButton*)AddGameObject(new ModeButton("Mode"));
	mode->sortLayer = 1;
	mode->SetTexture("sprites/UI/ModeSelect/SpringBreeze.png");
	mode->SetFocus(true);
	SpriteGO* guide = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/SpringBreezeGuide.png", "Guide"));
	guide->SetPosition({10.0f, 10.0f});
	guide->SetActive(false);
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
	if (Input.GetKeyDown(sf::Keyboard::X) && status == ModeSelectStatus::None)
	{
		SpriteGO* guide = (SpriteGO*)FindGameObject("Guide");
		guide->SetActive(true);
		status = ModeSelectStatus::Guide;
	}
	else if(Input.GetKeyDown(sf::Keyboard::X) && status == ModeSelectStatus::Guide)
	{
		SCENE_MANAGER.ChangeScene(SceneId::SpringBreeze);
	}
}

void SceneModeSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}