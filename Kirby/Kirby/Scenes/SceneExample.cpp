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
#include <Mob.h>
#include <ThrowableGround.h>
#include <Animator.h>
#include <Door.h>
#include <KirbyEffect.h>
#include "Camera.h"
#include <Cutter.h>
#include <StatusUI.h>
#include "MobPool.h"
//MapTool
#include <fstream>
#include "Item.h"
#include "Player.h"
#include "Ground.h"
#include "Enemy.h"
#include <SemiBossBomb.h>

SceneExample::SceneExample() 
	: Scene(SceneId::Title)
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
	worldView.setSize(size);

	Kirby* kirby = (Kirby*)FindGameObject("Kirby");
	worldView.setCenter(0.0f,0.0f);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	MobPool* mobPool = (MobPool*)FindGameObject("MobPool");
	for (int i = 0; i < rootNode["Enemy"].size(); i++)
	{
		Json::Value node = rootNode["Enemy"][i];
		Mob* mob = mobPool->GetMob((EnemyType)node["Type"].asInt());
		mob->sortLayer = node["SortLayer"].asInt();
		mob->SetRegenPosition({ node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() });
	}

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
	mobPool->ClearPool();
	Scene::Exit();
}

void SceneExample::Init()
{
	Scene::Init();
	Release();

	auto size = FRAMEWORK.GetWindowSize();

	//������ �����
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
	
	Controller* testController = (Controller*)AddGameObject(new Controller(*kirby, "Controller"));

	RectangleShapeGO* curtain = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Curtain"));
	curtain->SetSize(FRAMEWORK.GetWindowSize());
	curtain->SetOrigin(Origins::MC);
	curtain->sortLayer = INT_MAX;
	curtain->SetFillColor({ 0, 0, 0, 0 });
	curtain->SetPosition(FRAMEWORK.GetWindowSize() * 0.5f);

	//BeamEffect* beam = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamEffectRoot"));
	//beam->AddComponent(new Animator(*beam, "animations/Effect/Beam/Beam", "Beam"));
	//beam->SetPosition(-72.0f, 0.0f);
	//beam->SetEffectDirection({ 1.0f, 0.0f });

	//BeamEffect* beam2 = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamTail"));
	//beam2->AddComponent(new Animator(*beam2, "animations/Effect/Beam/Beam", "Beam"));
	//beam2->SetPosition(-82.0f, 0.0f);
	//beam2->SetEffectDirection({ 1.0f, 0.0f });
	//beam2->SetPrevNode(beam);

	//BeamEffect* beam3 = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamTail"));
	//beam3->AddComponent(new Animator(*beam3, "animations/Effect/Beam/Beam", "Beam"));
	//beam3->SetPosition(-92.0f, 0.0f);
	//beam3->SetEffectDirection({ 1.0f, 0.0f });
	//beam3->SetPrevNode(beam2);

	//BeamEffect* beam4 = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamEffectRoot"));
	//beam4->AddComponent(new Animator(*beam4, "animations/Effect/Beam/Beam", "Beam"));
	//beam4->SetPosition(0.0f, 0.0f);
	//beam4->SetEffectDirection({ 1.0f, 0.0f });

	//BeamEffect* beam5 = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamTail"));
	//beam5->AddComponent(new Animator(*beam5, "animations/Effect/Beam/Beam", "Beam"));
	//beam5->SetPosition(0.0f, 0.0f);
	//beam5->SetEffectDirection({ -1.0f, 0.0f });
	//beam5->SetPrevNode(beam4);

	MobPool* mobPool = (MobPool*)AddGameObject(new MobPool("MobPool"));
	LoadData(L"maps/Green_Green_3.json");
	//BeamEffect* beam6 = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamTail"));
	//beam6->AddComponent(new Animator(*beam6, "animations/Effect/Beam/Beam", "Beam"));
	//beam6->SetPosition(0.0f, 0.0f);
	//beam6->SetEffectDirection({ -1.0f, 0.0f });
	//beam6->SetPrevNode(beam5);

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
		kirby->SetPosition(ScreenToWorldPosition(Input.GetMousePosition()));
	}

	if (currentCamera != nullptr)
	{
		currentCamera->MoveCamera(deltaTime);
		std::list<GameObject*> goList;
		FindGameObjects(goList, "Ground");
		FindGameObjects(goList, "Mob");
		for (auto go : goList)
		{
			currentCamera->SetActiveInCamera((SpriteGO*)go);
		}
	}

	if (Input.GetKey(Keyboard::LShift))
	{
		if (Input.GetKeyDown(Keyboard::Num5))
		{
			//���� ī�޶� ����
			currentCamera->SetActive(false);
			currentCamera = previousCamera;
		}
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
	Scene::Draw(window);
}

void SceneExample::LoadData(const std::wstring& path)
{
	if (path == "")
	{
		return;
	}
	std::ifstream ifile(path);
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
	Json::Value cameraNodes = rootNode["Camera"];
	Json::Value ambientObjectNodes = rootNode["AmbientObject"];
	sf::Vector2f cellSize = { 24.0f, 24.0f };

	//Temp Background
	VertexArrayGO* background = CreateBackground({ 1, 1 }, { 1920.0f, 1080.0f });
	AddGameObject(background);
	background->SetOrigin(Origins::TL);
	background->SetPosition(0.f, 0.f);
	background->sortLayer = -99;

	Kirby* kirby = (Kirby*)FindGameObject("Kirby");
	kirby->sortLayer = rootNode["Player"]["SortLayer"].asInt();
	kirby->SetPosition({ rootNode["Player"]["Position"]["x"].asFloat() + 12.0f, rootNode["Player"]["Position"]["y"].asFloat() });

	for (int i = 0; i < itemNodes.size(); i++)
	{
		Json::Value node = itemNodes[i];
		ItemType type = (ItemType)node["Type"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		std::string textureId = "sprites/item/items.png";
		sf::IntRect rect;
		int sort = node["SortLayer"].asInt();
		switch (type)
		{
		case ItemType::Life:
			rect = { 216, 0, 24, 24};
			break;
		case ItemType::God:
			rect = { 216, 24, 24, 24 };
			break;
		case ItemType::MaxTomato:
			rect = { 96, 24, 24, 24 };
			break;
		case ItemType::Normal:
			rect = { 120, 24, 24, 24 };
			break;
		}
		SpriteGO* item = (SpriteGO*)AddGameObject(new SpriteGO(textureId, "item"));
		item->sprite.setTextureRect(rect);
		item->SetSize(cellSize);
		item->physicsLayer = (int)PhysicsLayer::Ground;
		item->sortLayer = sort;
		item->SetPosition(position);
	}



	for (int i = 0; i < doorNodes.size(); i++)
	{
		Json::Value node = doorNodes[i];
		DoorType type = (DoorType)node["Type"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() - 24.0f };
		sf::Vector2f movePosition = { node["MovePosition"]["x"].asFloat(), node["MovePosition"]["y"].asFloat()};
		int sort = node["SortLayer"].asInt();

		Door* door = (Door*)AddGameObject(new Door("", "Door"));
		door->physicsLayer = (int)PhysicsLayer::Interact;
		door->SetPosition(position);
		door->SetMovePosition(movePosition);
		BoxCollider* doorCol = (BoxCollider*)door->AddComponent(new BoxCollider(*door));
		doorCol->SetTrigger(true);
		doorCol->SetRect({ 0.0f, 0.0f, 24.0f, 48.0f });
	}

	for (int i = 0; i < groundNodes.size(); i++)
	{
		Json::Value node = groundNodes[i];
		if ((GroundType)node["Type"].asInt() == GroundType::Throught)
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
			ground->SetGroundType((GroundType)node["Type"].asInt());
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

		Camera* camPtr = (Camera*)AddGameObject(new Camera("camPtr" + std::to_string(i)));
		camPtr->SetType(type);
		camPtr->SetKirby(kirby);
		camPtr->SetData(node);
		camPtr->SetView(&worldView);
	}

	for (int i = 0; i < ambientObjectNodes.size(); i++)
	{
		Json::Value node = ambientObjectNodes[i];
	}
}

void SceneExample::SetCamera(Camera* camera)
{ 
	if (camera == nullptr)
	{
		this->currentCamera = previousCamera;
	}
	else
	{
		this->previousCamera = currentCamera;
		this->currentCamera = camera;
	}
}

VertexArrayGO* SceneExample::CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize, const std::string& textureId)
{
	VertexArrayGO* background = new VertexArrayGO(textureId, "Background");
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
				sf::Color color = sf::Color(57, 73, 92);
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