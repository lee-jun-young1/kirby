#include "stdafx.h"
#include "SceneModeSelect.h"
#include "GameObject.h"
#include "Framework.h"
#include "InputManager.h"
#include "SpriteGO.h"
#include "ModeButton.h"
#include "SceneManager.h"
#include "ModeSelectBoard.h"
#include <RectangleShapeGO.h>

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

	RectangleShapeGO* shape = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO());
	shape->sortLayer = 10;
	board->SetOutLine(shape);

	ModeButton* springBreeze = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/SpringBreeze.png", "Mode"));
	springBreeze->SetPosition(24.0f, 20.0f);
	springBreeze->sortLayer = 1;
	SpriteGO* guide1 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Guide.png", "Guide"));
	guide1->sprite.setTextureRect({ 0, 0, 198, 214 });
	guide1->SetPosition({ 10.0f, 10.0f });
	springBreeze->SetGuide(guide1);
	board->AddMode(springBreeze);

	ModeButton* gourmetRace = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/GourmetRace.png", "Mode"));
	gourmetRace->SetPosition(89.0f, 13.0f);
	gourmetRace->sortLayer = 1;
	SpriteGO* guide3 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Guide.png", "Guide"));
	guide3->sprite.setTextureRect({ 0, 423, 198, 214 });
	guide3->SetPosition({ 10.0f, 10.0f });
	gourmetRace->SetGuide(guide3);
	board->AddMode(gourmetRace);

	ModeButton* milkyWay = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/MilkWayWishes.png", "Mode"));
	milkyWay->SetPosition(176.0f, 22.0f);
	milkyWay->sortLayer = 1;
	milkyWay->SetLock(true);
	SpriteGO* guide5 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Guide.png", "Guide"));
	guide5->sprite.setTextureRect({ 0, 1056, 198, 214 });
	guide5->SetPosition({ 10.0f, 10.0f });
	milkyWay->SetGuide(guide5);
	board->AddMode(milkyWay);

	ModeButton* dynaBlade = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/DynaBlade.png", "Mode"));
	dynaBlade->SetPosition(17.0f, 84.0f);
	dynaBlade->sortLayer = 1;
	SpriteGO* guide2 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Guide.png", "Guide"));
	guide2->sprite.setTextureRect({ 0, 212, 198, 214 });
	guide2->SetPosition({ 10.0f, 10.0f });
	dynaBlade->SetGuide(guide2);
	board->AddMode(dynaBlade);

	ModeButton* caveOffensive = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/CaveOffensive.png", "Mode"));
	caveOffensive->SetPosition(74.0f, 77.0f);
	caveOffensive->sortLayer = 1;
	SpriteGO* guide4 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Guide.png", "Guide"));
	guide4->sprite.setTextureRect({ 0, 634, 198, 214 });
	guide4->SetPosition({ 10.0f, 10.0f });
	caveOffensive->SetGuide(guide4);
	board->AddMode(caveOffensive);

	ModeButton* revengeMeta = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/RevengeMeta.png", "Mode"));
	revengeMeta->SetPosition(129.0f, 70.0f);
	revengeMeta->sortLayer = 1;
	revengeMeta->SetLock(true);
	SpriteGO* guide6 = (SpriteGO*)AddGameObject(new SpriteGO("sprites/UI/ModeSelect/Guide.png", "Guide"));
	guide6->sprite.setTextureRect({ 0, 845, 198, 214 });
	guide6->SetPosition({ 10.0f, 10.0f });
	revengeMeta->SetGuide(guide6);
	board->AddMode(revengeMeta);

	ModeButton* megatonPunch = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/MegatonPunch.png", "Mode"));
	megatonPunch->SetPosition(137.0f, 142.0f);
	megatonPunch->sortLayer = 1;
	board->AddMode(megatonPunch);

	ModeButton* samuraiKirby = (ModeButton*)AddGameObject(new ModeButton("sprites/UI/ModeSelect/SamuraiKirby.png", "Mode"));
	samuraiKirby->SetPosition(154.0f, 158.0f);
	samuraiKirby->sortLayer = 1;
	board->AddMode(samuraiKirby);
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