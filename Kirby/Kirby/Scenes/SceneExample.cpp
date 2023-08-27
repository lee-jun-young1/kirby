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
#include <Utils.h>
#include <Controller.h>
#include <Kirby.h>
#include <ThrowableGround.h>
#include <Animator.h>
#include <Door.h>
#include <KirbyEffect.h>
#include "Camera.h"
#include <StatusUI.h>
#include "GenPoint.h"
#include "CameraArea.h"
#include "Background.h"
#include "BackgroundSea.h"
//MapTool
#include <fstream>
#include "Item.h"
#include "Player.h"
#include "Ground.h"
#include "Enemy.h"
//Enemy
#include "MobPool.h"
#include "Mob.h"
#include "Cutter.h"
#include "Bomb.h"
#include "Beam.h"
#include "Normal.h"
#include "Fly.h"
#include "Bear.h"
#include "Chick.h"
#include "Mushroom.h"
#include "SemiBossBomb.h"
#include <BossWood.h>
#include <WarpStar.h>

SceneExample::SceneExample() 
	: Scene(SceneId::Game)
{
	sceneName = "ExampleScene";
}

SceneExample::~SceneExample()
{
	Release();
}

void SceneExample::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	auto screenCenter = size * 0.5f;
	backgroundView.setSize(size);
	backgroundView.setCenter(screenCenter);
	
	worldView.setSize(size);
	worldView.setCenter(0.0f,0.0f);

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
	MobPool* mobPool = (MobPool*)FindGameObject("MobPool");
	mobPool->ClearAllPool();
	Scene::Exit();
}

void SceneExample::Init()
{
	Scene::Init();
	Release();

	auto size = FRAMEWORK.GetWindowSize();

	//윈도우 가운데로
	FRAMEWORK.GetWindow().setPosition(sf::Vector2i((1920 - size.x * 3.f) / 2, (1080 - size.y * 3.f) / 2));

	Kirby* kirby = (Kirby*)AddGameObject(new Kirby("sprites/kirby/Class_Normal.png", "Kirby"));
	kirby->AddTag("Kirby");
	kirby->physicsLayer = (int)PhysicsLayer::Player;

	Suction* suction = (Suction*)AddGameObject(new Suction("Suction"));
	suction->physicsLayer = (int)PhysicsLayer::Player;
	suction->SetKirby(kirby);
	suction->SetActive(false);
	kirby->SetSuction(suction);

	KirbyEffect* kirbyEffect = (KirbyEffect*)AddGameObject(new KirbyEffect("sprites/effects/KirbyEffect.png", "KirbyEffect"));
	kirbyEffect->physicsLayer = (int)PhysicsLayer::PlayerEffect;
	kirbyEffect->SetActive(false);
	Animator* effectAnimator = (Animator*)kirbyEffect->AddComponent(new Animator(*kirbyEffect, "animations/Effect/KirbyEffect", "Star"));
	RigidBody2D* effectRigidbody = (RigidBody2D*)kirbyEffect->AddComponent(new RigidBody2D(*kirbyEffect));
	BoxCollider* effectCollider = (BoxCollider*)kirbyEffect->AddComponent(new BoxCollider(*kirbyEffect));
	effectCollider->SetRect({ 0.0f, 0.0f, 20.0f, 20.0f });
	effectCollider->SetOffset({ 2.0f, 2.0f });
	effectCollider->SetTrigger(true);

	kirby->SetEffect(kirbyEffect);


	EffectPool* effectPool = (EffectPool*)AddGameObject(new EffectPool("EffectPool"));
	kirby->SetEffectPool(effectPool);

	SpriteTextGO* scoreText = (SpriteTextGO*)AddGameObject(new SpriteTextGO("fonts/ScoreFont_Data.csv"));
	scoreText->sortLayer = UILayer + 1;
	SpriteTextGO* liftText = (SpriteTextGO*)AddGameObject(new SpriteTextGO("fonts/ScoreFont_Data.csv"));
	liftText->sortLayer = UILayer + 1;
	StatusUI* ui = (StatusUI*)AddGameObject(new StatusUI("StatusUI"));
	ui->sortLayer = UILayer;
	ui->SetScoreText(scoreText);
	ui->SetLifeText(liftText);

	//BossWood* boss = (BossWood*)AddGameObject(new BossWood());
	//boss->AddTag("Mob");
	//boss->physicsLayer = (int)PhysicsLayer::Enemy;
	//boss->SetPosition(1154.0f, 1128.0f);
	//Animator* bossAnimator = (Animator*)boss->AddComponent(new Animator(*boss, "animations/Mob/Wood/Wood", "Idle"));
	//boss->SetAnimator(bossAnimator);
	//BoxCollider* bossCol = (BoxCollider*)boss->AddComponent(new BoxCollider(*boss));
	//bossCol->SetRect({ 0.0f, 0.0f, 24.0f * 3.0f, 24.0f * 5.0f });
	//bossCol->SetTrigger(true);
	//boss->SetEffectPool(effectPool);

	//Background
	Background* background = (Background*)AddGameObject(new Background("sprites/background/Green_Green_Background.png", "Background"));
	BackgroundSea* sea = (BackgroundSea*)AddGameObject(new BackgroundSea());

	Controller* testController = (Controller*)AddGameObject(new Controller(*kirby, "Controller"));

	WarpStar* warpStar = (WarpStar*)AddGameObject(new WarpStar());
	warpStar->physicsLayer = (int)PhysicsLayer::Interact;
	warpStar->SetPosition({ 792.0f, 48.0f });
	BoxCollider* warpStarCol = (BoxCollider*)warpStar->AddComponent(new BoxCollider(*warpStar));
	warpStarCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	warpStarCol->SetOffset({ 24.0f, 24.0f });
	warpStar->SetMovePosition({36.0f, 648.0f});

	RectangleShapeGO* curtain = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Curtain"));
	curtain->SetSize(FRAMEWORK.GetWindowSize());
	curtain->SetOrigin(Origins::MC);
	curtain->sortLayer = INT_MAX;
	curtain->SetFillColor({ 0, 0, 0, 0 });
	curtain->SetPosition(FRAMEWORK.GetWindowSize() * 0.5f);

	MobPool* mobPool = (MobPool*)AddGameObject(new MobPool("MobPool"));
	Camera* cam = (Camera*)AddGameObject(new Camera("Camera"));
	cam->SetKirby(kirby);
	cam->SetView(&worldView);
	cam->SetGameObjects(&gameObjects);
	cam->physicsLayer = (int)PhysicsLayer::Player;
	BoxCollider* camCol = (BoxCollider*)cam->AddComponent(new BoxCollider(*cam));
	camCol->SetTrigger(true);
	camCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	camCol->SetOffset({ -12.0f, -24.0f });
	
	LoadData(L"maps/Green_Green.bak.json");
	//LoadData(L"maps/temp.json");


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
	if (Input.GetKeyDown(Keyboard::F11))
	{
		SCENE_MANAGER.ChangeScene(SceneId::MapTool);
	}
	Kirby* kirby = (Kirby*)FindGameObject("Kirby");
	if (Input.GetMouseButtonDown(sf::Mouse::Left))
	{
		//kirby->SetPosition(ScreenToWorldPosition(Input.GetMousePosition()));
		cout << ScreenToWorldPosition(Input.GetMousePosition()).x << ", " << ScreenToWorldPosition(Input.GetMousePosition()).y << endl;
	}
	if (Input.GetKeyDown(sf::Keyboard::Num9))
	{
		kirby->SetPosition({ 1000.0f, 1128.0f });
	}
	if (Input.GetKeyDown(sf::Keyboard::Num0))
	{
		kirby->SetPosition({ 700.0f, 660.0f });
	}

	if (Input.GetKeyDown(Keyboard::Num1))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetUIMode(StatusUI::UIMode::Default);
	}

	if (Input.GetKeyDown(Keyboard::Num2))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetUIMode(StatusUI::UIMode::Boss);
	}

	if (Input.GetKeyDown(Keyboard::Num3))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetUIMode(StatusUI::UIMode::WithPartner);
	}

	if (Input.GetKeyDown(Keyboard::Num4))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetUIMode(StatusUI::UIMode::BossWithPartner);
	}

	if (Input.GetKeyDown(Keyboard::Numpad1))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetPlayer1HP(0.0f);
		kirby->Damage(50,1);
	}

	if (Input.GetKeyDown(Keyboard::Numpad2))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetPlayer1HP(0.5f);
	}

	if (Input.GetKeyDown(Keyboard::Numpad3))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetPlayer1HP(1.0f);
	}

	if (Input.GetKeyDown(Keyboard::Numpad4))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetEnemyHP(0.0f);
	}

	if (Input.GetKeyDown(Keyboard::Numpad5))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetEnemyHP(0.5f);
	}

	if (Input.GetKeyDown(Keyboard::Numpad6))
	{
		StatusUI* ui = (StatusUI*)FindGameObject("StatusUI");
		ui->SetEnemyHP(1.0f);
	}

	if (Input.GetKeyDown(Keyboard::F5))
	{
		Mob* suctionAble = (Mob*)AddGameObject(new Mob(KirbyAbility::None, "sprites/mob/mob_normal.png", "Suctionable"));
		suctionAble->AddTag("Suctionable");
		suctionAble->AddTag("Mob");
		suctionAble->SetSize({ 24.0f, 24.0f });
		suctionAble->physicsLayer = (int)PhysicsLayer::Enemy;
		suctionAble->SetPosition(FindGameObject("Kirby")->GetPosition() + sf::Vector2f(144.0f, -144.0f));
		BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
		RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
		suctionAbleCol->SetRigidbody(rig);
		Animator* ani = (Animator*)suctionAble->AddComponent(new Animator(*suctionAble, "animations/Mob/Normal/Normal", "Move"));
		suctionAble->SetAnimator(ani);
		suctionAble->SetRigidBody(rig);

		suctionAble->Reset();
		suctionAble->SetPosition(ScreenToWorldPosition({ 72.0f, -72.0f }));
		suctionAble->SetOrigin({ 36.0f, 48.0f });
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ -12.0f, -24.0f });
		
	}

	if (Input.GetKeyDown(Keyboard::F6))
	{
		Cutter* suctionAble = (Cutter*)AddGameObject(new Cutter(KirbyAbility::Cutter, "sprites/mob/mob_Cutter.png", "Cutter"));
		suctionAble->AddTag("Suctionable");
		suctionAble->AddTag("Mob");
		suctionAble->SetSize({ 24.0f, 24.0f });
		suctionAble->physicsLayer = (int)PhysicsLayer::Enemy;
		suctionAble->SetOrigin(Origins::BC);
		BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ 0.0f, -24.0f });
		RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
		suctionAbleCol->SetRigidbody(rig);
		Animator* ani = (Animator*)suctionAble->AddComponent(new Animator(*suctionAble, "animations/Mob/Cutter/Cutter", "Idle"));
		suctionAble->SetAnimator(ani);
		suctionAble->SetRigidBody(rig);

		suctionAble->Reset();
		suctionAble->SetPosition(ScreenToWorldPosition({ 72.0f, -72.0f }));
		suctionAble->SetOrigin({ 36.0f, 48.0f });
		suctionAble->SetPosition(-10.0f, 0.0f);
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ -12.0f, -24.0f });
	}

	if (Input.GetKeyDown(Keyboard::F7))
	{
		Mob* suctionAble = (Mob*)AddGameObject(new Mob(KirbyAbility::Beam, "sprites/mob/Mob_Beam.png", "Suctionable"));
		suctionAble->AddTag("Suctionable");
		suctionAble->AddTag("Mob");
		suctionAble->SetSize({ 24.0f, 24.0f });
		suctionAble->physicsLayer = (int)PhysicsLayer::Enemy;
		suctionAble->SetOrigin(Origins::BC);
		suctionAble->SetPosition(FindGameObject("Kirby")->GetPosition() + sf::Vector2f(144.0f, -144.0f));
		BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ 0.0f, -24.0f });
		RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
		suctionAbleCol->SetRigidbody(rig);

		Animator* ani = (Animator*)suctionAble->AddComponent(new Animator(*suctionAble, "animations/Mob/Beam/Beam", "Move"));
		suctionAble->SetAnimator(ani);
		suctionAble->SetRigidBody(rig);

		suctionAble->Reset();
		suctionAble->SetPosition(ScreenToWorldPosition({ 72.0f, -72.0f }));
		suctionAble->SetOrigin({ 36.0f, 48.0f });
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ -12.0f, -24.0f });
	}

	if (Input.GetKeyDown(Keyboard::F8))
	{
		Mob* suctionAble = (Mob*)AddGameObject(new Mob(KirbyAbility::Bomb, "sprites/mob/mob_Bomb.png", "Suctionable"));
		suctionAble->AddTag("Suctionable");
		suctionAble->AddTag("Mob");
		suctionAble->SetSize({ 24.0f, 24.0f });
		suctionAble->physicsLayer = (int)PhysicsLayer::Enemy;
		suctionAble->SetOrigin(Origins::BC);
		suctionAble->SetPosition(FindGameObject("Kirby")->GetPosition() + sf::Vector2f(72.0f, -72.0f));
		BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ 0.0f, -24.0f });
		RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
		suctionAbleCol->SetRigidbody(rig);

		Animator* ani = (Animator*)suctionAble->AddComponent(new Animator(*suctionAble, "animations/Mob/Bomb/Bomb", "Jump"));
		suctionAble->SetAnimator(ani);
		suctionAble->SetRigidBody(rig);

		suctionAble->Reset();
		suctionAble->SetPosition(ScreenToWorldPosition({ 72.0f, -72.0f }));
		suctionAble->SetOrigin({ 36.0f, 48.0f });
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ -12.0f, -24.0f });
	}

	if (Input.GetKeyDown(Keyboard::F9))
	{
		SemiBossBomb* suctionAble = (SemiBossBomb*)AddGameObject(new SemiBossBomb(KirbyAbility::Bomb, "sprites/mob/SB_Bomb.png", "Suctionable"));
		suctionAble->AddTag("Mob");
		suctionAble->SetSize({ 24.0f, 24.0f });
		suctionAble->physicsLayer = (int)PhysicsLayer::Enemy;
		suctionAble->SetOrigin(Origins::BC);
		BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ 0.0f, -24.0f });
		RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
		suctionAbleCol->SetRigidbody(rig);

		Animator* ani = (Animator*)suctionAble->AddComponent(new Animator(*suctionAble, "animations/Mob/SB-Bomb/SB-Bomb", "Jump"));
		suctionAble->SetAnimator(ani);
		suctionAble->SetRigidBody(rig);
		EffectPool* effectPool = (EffectPool*)FindGameObject("EffectPool");
		suctionAble->SetEffectPool(effectPool);

		suctionAble->Reset();
		suctionAble->SetPosition(ScreenToWorldPosition({ 72.0f, -72.0f }));
		suctionAble->SetOrigin({ 36.0f, 48.0f });
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ -12.0f, -24.0f });
	}

}

void SceneExample::Draw(sf::RenderWindow& window)
{
	SortGameObjects();

	window.setView(backgroundView);
	for (auto go : gameObjects)
	{
		if (go->sortLayer > backgroundLayer)
		{
			continue;
		}
		if (go->IsActive())
		{
			go->Draw(window);
		}
	}

	window.setView(worldView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer <= backgroundLayer || go->sortLayer >= UILayer)
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

void SceneExample::LoadData(const std::wstring& path)
{
	if (path == "")
	{
		return;
	}
	std::ifstream ifile(path);
	Json::Value rootNode;
	if (ifile.is_open())
	{
		ifile >> rootNode;
		ifile.close();
	}
	else
	{
		std::wcout << "File Open Error! Path: " << path << std::endl;
		return;
	}

	Json::Value itemNodes = rootNode["Item"];
	Json::Value doorNodes = rootNode["Door"];
	Json::Value groundNodes = rootNode["Ground"];
	Json::Value enemyNodes = rootNode["Enemy"];
	Json::Value cameraNodes = rootNode["Camera"];
	Json::Value ambientObjectNodes = rootNode["AmbientObject"];
	sf::Vector2f cellSize = { 24.0f, 24.0f };


	Kirby* kirby = (Kirby*)FindGameObject("Kirby");
	kirby->sortLayer = rootNode["Player"]["SortLayer"].asInt();
	kirby->SetPosition({ rootNode["Player"]["Position"]["x"].asFloat() + 12.0f, rootNode["Player"]["Position"]["y"].asFloat() });
	Camera* cam = (Camera*)FindGameObject("Camera");
	cam->SetPosition(kirby->GetPosition());

	for (int i = 0; i < itemNodes.size(); i++)
	{
		Json::Value node = itemNodes[i];
		Item* item = (Item*)AddGameObject(new Item("sprites/item/items.png", "Item"));
		item->SetOrigin(Origins::BC);
		item->SetItemType((ItemType)node["Type"].asInt());
		item->physicsLayer = (int)PhysicsLayer::Item;
		item->sortLayer = node["SortLayer"].asInt();
		item->SetPosition({ node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() });
		item->SetKirby(kirby);
		BoxCollider* boxCol = (BoxCollider*)item->AddComponent(new BoxCollider(*item));
		boxCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		boxCol->SetOffset({ 0.0f, 0.0f });
	}

	MobPool* mobPool = (MobPool*)FindGameObject("MobPool");
	for (int i = 0; i < enemyNodes.size(); i++)
	{
		Json::Value node = enemyNodes[i];
		int sort = node["SortLayer"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		EnemyType type = (EnemyType)node["Type"].asInt();

		GenPoint* genPoint = (GenPoint*)AddGameObject(new GenPoint("GenPoint"));
		genPoint->SetEnemyType(type);
		genPoint->SetPosition(position);
		genPoint->sortLayer = sort;
		genPoint->SetMobPool(mobPool);
	}

	for (int i = 0; i < doorNodes.size(); i++)
	{
		Json::Value node = doorNodes[i];
		DoorType type = (DoorType)node["Type"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() - 24.0f };
		sf::Vector2f movePosition = { node["MovePosition"]["x"].asFloat(), node["MovePosition"]["y"].asFloat()};
		int sort = node["SortLayer"].asInt();

		Door* door = (Door*)AddGameObject(new Door("", "Door"));
		door->physicsLayer = (int)PhysicsLayer::Ground;
		door->SetPosition(position);
		door->SetMovePosition(movePosition);
		BoxCollider* doorCol = (BoxCollider*)door->AddComponent(new BoxCollider(*door));
		doorCol->SetTrigger(true);
		doorCol->SetRect({ 0.0f, 0.0f, 24.0f, 48.0f });
	}

	for (int i = 0; i < groundNodes.size(); i++)
	{
		Json::Value node = groundNodes[i];
		GroundType type = (GroundType)node["Type"].asInt();
		int sort = node["SortLayer"].asInt();
		bool flipX = node["FlipX"].asBool();
		sf::IntRect rect = { node["TexturePosition"]["x"].asInt(), node["TexturePosition"]["y"].asInt(), (int)cellSize.x, (int)cellSize.y };
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };

		if (type == GroundType::Throught)
		{
			ThroughtableGround* throughtGround = (ThroughtableGround*)AddGameObject(new ThroughtableGround());
			throughtGround->AddTag("Ground");
			throughtGround->SetSize({ 24.0f, 24.0f });
			throughtGround->physicsLayer = (int)PhysicsLayer::Ground;
			throughtGround->SetOrigin(Origins::MC);
			throughtGround->SetPosition(node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat());
			BoxCollider* throughtGroundCol = (BoxCollider*)throughtGround->AddComponent(new BoxCollider(*throughtGround));
			throughtGround->SetCollider(throughtGroundCol);
		}
		else
		{
			Ground* ground = (Ground*)AddGameObject(new Ground(rootNode["Path"].asString(), "Ground"));
			ground->SetData(node);
			ground->SetGroundType(type);
			ground->SetTextureRect(rect);
			ground->SetPosition(position);
			ground->sprite.setTextureRect(rect);
			//if (node["FlipX"].asBool())
			//{
			//	ground->SetFlipX(true);
			//	ground->SetOrigin({ (!flipX) ? cellSize.x : 0.f, 0.f });
			//}
			switch (type)
			{
			case GroundType::Normal:
			{
				BoxCollider* boxCol = (BoxCollider*)ground->AddComponent(new BoxCollider(*ground));
				boxCol->SetRect({ (float)rect.left, (float)rect.top, (float)rect.width, (float)rect.height });
				if (flipX)
				{
					boxCol->SetOffset({ node["OffSet"]["x"].asFloat(), node["OffSet"]["y"].asFloat() });
				}
				else
				{
					boxCol->SetOffset({ node["OffSet"]["x"].asFloat(), node["OffSet"]["y"].asFloat() });
				}
			}
			break;
			case GroundType::Tilted:
			{
				BoxCollider* boxCol = (BoxCollider*)ground->AddComponent(new BoxCollider(*ground));
				boxCol->SetRect({ (float)rect.left, (float)rect.top, (float)rect.width + 2.0f, (float)rect.height * 0.01f });
				if (flipX)
				{
					boxCol->SetRotationOffset(node["Angle"].asFloat() * -1);
					boxCol->SetOffset({ node["OffSet"]["x"].asFloat() + 1.0f, node["OffSet"]["y"].asFloat()});
				}
				else
				{
					boxCol->SetRotationOffset(node["Angle"].asFloat());
					boxCol->SetOffset({ node["OffSet"]["x"].asFloat() - 1.0f, node["OffSet"]["y"].asFloat()});
				}
			}
			break;
			case GroundType::Throught:
				break;
			case GroundType::Background:
				break;
			case GroundType::Crashed:
				break;
			case GroundType::Transpar:
			{
				BoxCollider* boxCol = (BoxCollider*)ground->AddComponent(new BoxCollider(*ground));
				boxCol->SetRect({ (float)rect.left, (float)rect.top, (float)rect.width, (float)rect.height });
				ground->sprite.setColor(sf::Color::Transparent);
			}
			break;
			}
		}
	}

	for (int i = 0; i < cameraNodes.size(); i++)
	{
		Json::Value node = cameraNodes[i];
		CameraType type = (CameraType)node["Type"].asInt();
		
		if (type == CameraType::MapEnd)
		{
			continue;
		}
		if (type == CameraType::MapStart)
		{
			type = CameraType::Free;
		}
		sf::Vector2f size;
		size.x = node["EndPosition"]["x"].asFloat() - node["Position"]["x"].asFloat() + cellSize.x;
		size.y = node["EndPosition"]["y"].asFloat() - node["Position"]["y"].asFloat() + cellSize.y;
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() + 24.0f };

		CameraArea* area = (CameraArea*)AddGameObject(new CameraArea("CameraArea"));
		area->SetType(type);
		area->SetPosition(position);
		area->SetSize(size);
		area->physicsLayer = (int)PhysicsLayer::Ground;
		area->SetCamera(cam);
		BoxCollider* col = (BoxCollider*)area->AddComponent(new BoxCollider(*area));
		col->SetTrigger(true);
	}

	for (int i = 0; i < ambientObjectNodes.size(); i++)
	{
		Json::Value node = ambientObjectNodes[i];
	}
}