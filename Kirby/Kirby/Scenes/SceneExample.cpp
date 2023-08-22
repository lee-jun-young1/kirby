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
#include "CameraPointer.h"
#include <Cutter.h>
#include <StatusUI.h>

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

	auto size = FRAMEWORK.GetWindowSize();

	//윈도우 가운데로
	FRAMEWORK.GetWindow().setPosition(sf::Vector2i((1920 - size.x * 3.f) / 2, (1080 - size.y * 3.f) / 2));

	Kirby* kirby = (Kirby*)AddGameObject(new Kirby("sprites/kirby/Class_Normal.png", "Kirby"));
	kirby->physicsLayer = (int)PhysicsLayer::Player;
	kirby->sortLayer = 1;
	kirby->SetPosition({ -80.0f, 0.0f });
	kirby->AddTag("Kirby");
	
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
	effectCollider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	effectCollider->SetTrigger(true);

	kirby->SetEffect(kirbyEffect);

	EffectPool* effectPool = (EffectPool*)AddGameObject(new EffectPool("EffectPool"));
	kirby->SetEffectPool(effectPool);

	//CameraPointer* tempCamPtr1 = (CameraPointer*)AddGameObject(new CameraPointer("tempCamPtr"));
	//tempCamPtr1->SetSize({ 80.0f * 2.0f, size.y });
	//tempCamPtr1->physicsLayer = (int)PhysicsLayer::Ground;
	//tempCamPtr1->SetOrigin(Origins::MC);
	//tempCamPtr1->SetType(CameraType::Fixed);
	//tempCamPtr1->SetPosition({ 0.0f, 0.0f });
	//BoxCollider* camCol1 = (BoxCollider*)tempCamPtr1->AddComponent(new BoxCollider(*tempCamPtr1));
	//camCol1->SetTrigger(true);

	SpriteTextGO* scoreText = (SpriteTextGO*)AddGameObject(new SpriteTextGO("fonts/ScoreFont_Data.csv"));
	scoreText->sortLayer = UILayer + 1;
	SpriteTextGO* liftText = (SpriteTextGO*)AddGameObject(new SpriteTextGO("fonts/ScoreFont_Data.csv"));
	liftText->sortLayer = UILayer + 1;
	StatusUI* ui = (StatusUI*)AddGameObject(new StatusUI("StatusUI"));
	ui->sortLayer = UILayer;
	ui->SetScoreText(scoreText);
	ui->SetLifeText(liftText);

	//RectangleShapeGO* tempGround1 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	//tempGround1->SetSize({ 24.0f, 24.0f });
	//tempGround1->physicsLayer = (int)PhysicsLayer::Ground;
	//tempGround1->SetOrigin(Origins::BC);
	//tempGround1->SetPosition(kirby->GetPosition() + sf::Vector2f(24.0f, -24.0f));
	//BoxCollider* boxCol1 = (BoxCollider*)tempGround1->AddComponent(new BoxCollider(*tempGround1));

	//for (int i = 0; i < 4; i++)
	//{
	/*Mob* suctionAble = (Mob*)AddGameObject(new Mob((KirbyAbility)i, "", "Suctionable"));
	suctionAble->SetSize({ 24.0f, 24.0f });
	suctionAble->physicsLayer = (int)PhysicsLayer::Ground;
	suctionAble->SetOrigin(Origins::BC);
	suctionAble->SetPosition(kirby->GetPosition() + sf::Vector2f(-24.0f + i * 48.0f, 0.0f));
	BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
	suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	suctionAbleCol->SetOffset({ 0.0f, -24.0f });
	RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
	suctionAbleCol->SetRigidbody(rig);
	rig->SetGravity(false);*/
	//}


	Controller* testController = (Controller*)AddGameObject(new Controller(*kirby, "Controller"));

	//RectangleShapeGO* tempGround = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	//tempGround->SetSize({ 106.0f, 20.0f });
	//tempGround->physicsLayer = (int)PhysicsLayer::Ground;
	//tempGround->SetOrigin(Origins::BC);
	//tempGround->SetPosition({ 0.0f, 100.0f });
	//BoxCollider* boxCol = (BoxCollider*)tempGround->AddComponent(new BoxCollider(*tempGround));


	for (float screenX = worldView.getSize().x * 0.33f * -0.5f; screenX < 1920.f * 0.33f * 0.5f; screenX += 24.0f)
	{
		RectangleShapeGO* tempGround1 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
		tempGround1->AddTag("Ground");
		tempGround1->SetSize({ 24.0f, 24.0f });
		tempGround1->physicsLayer = (int)PhysicsLayer::Ground;
		tempGround1->SetOrigin(Origins::MC);
		//tempGround2->SetPosition({ 0.0f, 100.0f });
		tempGround1->SetPosition({ screenX, 80.0f + 33.0f * 0.5f });
		BoxCollider* boxCol = (BoxCollider*)tempGround1->AddComponent(new BoxCollider(*tempGround1));
	}
	for (int i = 1; i < 4; i++)
	{
		RectangleShapeGO* tempGround1 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
		tempGround1->AddTag("Ground");
		tempGround1->SetSize({ 24.0f, 24.0f });
		tempGround1->physicsLayer = (int)PhysicsLayer::Ground;
		tempGround1->SetOrigin(Origins::MC);
		//tempGround2->SetPosition({ 0.0f, 100.0f });
		tempGround1->SetPosition({ worldView.getSize().x * 0.33f * -0.5f + 24.0f, 80.0f + (-24.0f * i) + 33.0f * 0.5f });
		BoxCollider* boxColg = (BoxCollider*)tempGround1->AddComponent(new BoxCollider(*tempGround1));

		RectangleShapeGO* tempGround2 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
		tempGround2->AddTag("Ground");
		tempGround2->SetSize({ 24.0f, 24.0f });
		tempGround2->physicsLayer = (int)PhysicsLayer::Ground;
		tempGround2->SetOrigin(Origins::MC);
		//tempGround2->SetPosition({ 0.0f, 100.0f });
		tempGround2->SetPosition({ worldView.getSize().x * 0.33f * -0.5f + 24.0f, 80.0f + (-24.0f * i) + 33.0f * 0.5f });
		BoxCollider* boxColg2 = (BoxCollider*)tempGround2->AddComponent(new BoxCollider(*tempGround2));
	}


	RectangleShapeGO* tempTiltedGround1 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	tempTiltedGround1->AddTag("Ground");
	tempTiltedGround1->SetSize({ 24.0f, 24.0f });
	tempTiltedGround1->physicsLayer = (int)PhysicsLayer::Ground;
	tempTiltedGround1->SetOrigin(Origins::MC);
	//tempGround2->SetPosition({ 0.0f, 100.0f });
	tempTiltedGround1->SetPosition({ -33.0f * 0.5f, 70.0f + 33.0f * 0.5f });
	tempTiltedGround1->SetRotation(-135.0f);
	BoxCollider* boxCol = (BoxCollider*)tempTiltedGround1->AddComponent(new BoxCollider(*tempTiltedGround1));

	RectangleShapeGO* tempTiltedGround3 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	tempTiltedGround3->AddTag("Ground");
	tempTiltedGround3->SetSize({ 24.0f, 24.0f });
	tempTiltedGround3->physicsLayer = (int)PhysicsLayer::Ground;
	tempTiltedGround3->SetOrigin(Origins::MC);
	//tempGround2->SetPosition({ 0.0f, 100.0f });
	tempTiltedGround3->SetPosition({ 33.0f * 0.5f, 70.0f + 33.0f * 0.5f });
	tempTiltedGround3->SetRotation(-135.0f);
	BoxCollider* boxCol3 = (BoxCollider*)tempTiltedGround3->AddComponent(new BoxCollider(*tempTiltedGround3));

	RectangleShapeGO* tempTiltedGround2 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	tempTiltedGround2->AddTag("Ground");
	tempTiltedGround2->SetSize({ 24.0f, 24.0f });
	tempTiltedGround2->physicsLayer = (int)PhysicsLayer::Ground;
	tempTiltedGround2->SetOrigin(Origins::MC);
	//tempGround2->SetPosition({ 0.0f, 100.0f });
	tempTiltedGround2->SetPosition({ 0.0f, 70.0f });
	tempTiltedGround2->SetRotation(-135.0f);
	BoxCollider* boxCol2 = (BoxCollider*)tempTiltedGround2->AddComponent(new BoxCollider(*tempTiltedGround2));

	for (float screenX = 24.0f; screenX < 1920.f * 0.33f * 0.5f; screenX += 24.0f)
	{
		RectangleShapeGO* tempGround1 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
		tempGround1->AddTag("Ground");
		tempGround1->SetSize({ 24.0f, 24.0f });
		tempGround1->physicsLayer = (int)PhysicsLayer::Ground;
		tempGround1->SetOrigin(Origins::MC);
		//tempGround2->SetPosition({ 0.0f, 100.0f });
		tempGround1->SetPosition({ screenX, 56.0f + 33.0f * 0.5f });
		BoxCollider* boxCol = (BoxCollider*)tempGround1->AddComponent(new BoxCollider(*tempGround1));
	}

	for (float screenX = worldView.getSize().x * 0.33f * 0.5f; screenX > 24.0f; screenX -= 24.0f)
	{
		ThroughtableGround* tempThroughtGround1 = (ThroughtableGround*)AddGameObject(new ThroughtableGround());
		tempThroughtGround1->AddTag("Ground");
		tempThroughtGround1->SetSize({ 24.0f, 24.0f });
		tempThroughtGround1->physicsLayer = (int)PhysicsLayer::Ground;
		tempThroughtGround1->SetOrigin(Origins::MC);
		tempThroughtGround1->SetPosition({ screenX, 80.0f + 33.0f * 0.5f - 36.0f - 24.0f -48.0f });
		BoxCollider* boxThroughtCol1 = (BoxCollider*)tempThroughtGround1->AddComponent(new BoxCollider(*tempThroughtGround1));
		tempThroughtGround1->SetCollider(boxThroughtCol1);

		ThroughtableGround* tempThroughtGround2 = (ThroughtableGround*)AddGameObject(new ThroughtableGround());
		tempThroughtGround2->AddTag("Ground");
		tempThroughtGround2->SetSize({ 24.0f, 24.0f });
		tempThroughtGround2->physicsLayer = (int)PhysicsLayer::Ground;
		tempThroughtGround2->SetOrigin(Origins::MC);
		tempThroughtGround2->SetPosition({ screenX, 80.0f + 33.0f * 0.5f - 36.0f - 24.0f });
		BoxCollider* boxThroughtCol2 = (BoxCollider*)tempThroughtGround2->AddComponent(new BoxCollider(*tempThroughtGround2));
		tempThroughtGround2->SetCollider(boxThroughtCol2);
	}

	Door* tempDoor = (Door*)AddGameObject(new Door("sprites/temp/Door.png", "Door"));
	tempDoor->physicsLayer = (int)PhysicsLayer::Interact;
	tempDoor->SetOrigin(Origins::BC);
	tempDoor->SetPosition({ -72.0f - 10.0f, 80.0f + 33.0f * 0.5f - 36.0f - 24.0f });
	tempDoor->SetMovePosition({ 240.f + 12.f, 80.0f + 33.0f * 0.5f - 36.0f + 24.0f - 0.3f });
	BoxCollider* doorCol1 = (BoxCollider*)tempDoor->AddComponent(new BoxCollider(*tempDoor));
	doorCol1->SetTrigger(true);
	doorCol1->SetRect({ 0.0f, 0.0f, 24.0f, 48.0f });

	Door* tempDoor2 = (Door*)AddGameObject(new Door("sprites/temp/Door.png", "Door"));
	tempDoor2->physicsLayer = (int)PhysicsLayer::Ground;
	tempDoor2->SetOrigin(Origins::BC);
	tempDoor2->SetPosition({ 240.f, 80.0f + 33.0f * 0.5f - 36.0f - 24.0f });
	tempDoor2->SetMovePosition({ -72.0f - 10.0f, 80.0f + 33.0f * 0.5f - 36.0f + 24.0f - 0.3f });
	BoxCollider* doorCol2 = (BoxCollider*)tempDoor2->AddComponent(new BoxCollider(*tempDoor2));
	doorCol2->SetTrigger(true);
	doorCol2->SetRect({ 0.0f, 0.0f, 24.0f, 48.0f });

	//RectangleShapeGO* tempGround3 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	//tempGround3->SetSize({ 106.0f, 20.0f });
	//tempGround3->physicsLayer = (int)PhysicsLayer::Ground;
	//tempGround3->SetOrigin(Origins::BC);
	//tempGround3->SetPosition({ -50.0f, 50.0f });
	//BoxCollider* boxCol3 = (BoxCollider*)tempGround3->AddComponent(new BoxCollider(*tempGround3));
	//boxCol3->SetRotationOffset(180.0f);

	//RectangleShapeGO* smallRectGO = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("SmallRect"));
	//smallRectGO->SetSize({ 10.0f, 10.0f });
	//smallRectGO->physicsLayer = (int)PhysicsLayer::Ground;
	//smallRectGO->SetOrigin(Origins::MC);
	//smallRectGO->SetPosition({ -20.0f, -20.0f });
	//BoxCollider* smallBoxCol = (BoxCollider*)smallRectGO->AddComponent(new BoxCollider(*smallRectGO));
	//smallBoxCol->SetRotationOffset(30.0f);

	//CircleShapeGO* circleGO = (CircleShapeGO*)AddGameObject(new CircleShapeGO("Circle"));
	//circleGO->SetSize({ 10.0f, 10.0f });
	//circleGO->physicsLayer = (int)PhysicsLayer::Ground;
	//circleGO->SetPosition({ 20.0f, 20.0f });
	//circleGO->SetOrigin(Origins::MC);
	//CircleCollider* circleCol = (CircleCollider*)circleGO->AddComponent(new CircleCollider(*circleGO));

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

	//BeamEffect* beam6 = (BeamEffect*)AddGameObject(new BeamEffect("sprites/effects/Beam_Effect.png", "BeamTail"));
	//beam6->AddComponent(new Animator(*beam6, "animations/Effect/Beam/Beam", "Beam"));
	//beam6->SetPosition(0.0f, 0.0f);
	//beam6->SetEffectDirection({ -1.0f, 0.0f });
	//beam6->SetPrevNode(beam5);
	cameraType = CameraType::Free;

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
	Kirby* kirby = (Kirby*)FindGameObject("Kirby");

	cameraTime += deltaTime * 2.0f;
	sf::Vector2f targetPoint;
	switch (cameraType)
	{
	case CameraType::Free:
		targetPoint = kirby->GetPosition();
		break;
	case CameraType::Horizontal:
		targetPoint = { kirby->GetPosition().x, worldView.getCenter().y };
		break;
	case CameraType::Vertical:
		targetPoint = { worldView.getCenter().x, kirby->GetPosition().y };
		break;
	case CameraType::Fixed:
		CameraPointer* camPtr = (CameraPointer*)FindGameObject("tempCamPtr");
		targetPoint = camPtr->GetPosition() * 0.5f;
		break;
	}
	worldView.setCenter(Utils::Lerp(worldView.getCenter(), targetPoint, cameraTime));
	cameraTime = 0.0f;

	if (Input.GetKey(Keyboard::LShift))
	{
		if (Input.GetKeyDown(Keyboard::Num1))
		{
			cameraType = CameraType::Free;
		}
		else if (Input.GetKeyDown(Keyboard::Num2))
		{
			cameraType = CameraType::Horizontal;
		}
		else if (Input.GetKeyDown(Keyboard::Num3))
		{
			cameraType = CameraType::Vertical;
		}
		else if (Input.GetKeyDown(Keyboard::Num4))
		{
			cameraType = CameraType::Fixed;
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
		suctionAble->SetPosition(10.0f, 0.0f);
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
		suctionAble->SetPosition(0.0f, 0.0f);
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
		suctionAble->SetPosition(0.0f, 0.0f);
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

	//RectangleShapeGO* rectGO = (RectangleShapeGO*)FindGameObject("Rect");


	//float axis = 0.0;
	//if (Input.GetKey(Keyboard::Num1))
	//{
	//	axis = -1.0f;
	//}
	//if (Input.GetKey(Keyboard::Num2))
	//{
	//	axis = 1.0f;
	//}

	//float axis2 = 0.0;
	//if (Input.GetKey(Keyboard::Num3))
	//{
	//	axis2 = -1.0f;
	//}
	//if (Input.GetKey(Keyboard::Num4))
	//{
	//	axis2 = 1.0f;
	//}

	//BoxCollider* rectCol = (BoxCollider*)rectGO->GetComponent(ComponentType::Collider);

	//rectCol->SetRotationOffset(rectCol->GetRotationOffset() + axis2 * 30.0f * deltaTime);

	//rectGO->SetRotation(rectGO->GetRotation() + axis * 30.0f * deltaTime);


	//float axis3 = 0.0;
	//if (Input.GetKey(Keyboard::Num5))
	//{
	//	axis3 = -1.0f;
	//}
	//if (Input.GetKey(Keyboard::Num6))
	//{
	//	axis3 = 1.0f;
	//}

	//RectangleShapeGO* rectGO2 = (RectangleShapeGO*)FindGameObject("SmallRect");


	//BoxCollider* rectCol2 = (BoxCollider*)rectGO2->GetComponent(ComponentType::Collider);

	//rectCol2->SetRotationOffset(rectCol2->GetRotationOffset() + axis3 * 30.0f * deltaTime);




	//rectGO->SetPosition({ rectGO->GetPosition().x + Input.GetAxisRaw(Axis::Horizontal) * 30.0f * deltaTime, rectGO->GetPosition().y + Input.GetAxisRaw(Axis::Vertical) * 30.0f * deltaTime });

	//CircleShapeGO* circleGO = (CircleShapeGO*)FindGameObject("Circle");
	////circleGO->SetPosition(Utils::RotateWithPivot(rectGO->GetPosition(), circleGO->GetPosition(), 30.0f * deltaTime));
	if (Input.GetKeyDown(Keyboard::F11))
	{
		SCENE_MANAGER.ChangeScene(SceneId::MapTool);
	}
}

void SceneExample::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
