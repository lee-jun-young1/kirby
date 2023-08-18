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

//MapTool
#include <fstream>
#include "Item.h"
#include "Player.h"
#include "Ground.h"
#include "Enemy.h"

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

	LoadData(L"maps/temp.json");

	auto size = FRAMEWORK.GetWindowSize();

	//윈도우 가운데로
	FRAMEWORK.GetWindow().setPosition(sf::Vector2i((1920 - size.x * 3.f) / 2, (1080 - size.y * 3.f) / 2));

	//Kirby* kirby = (Kirby*)AddGameObject(new Kirby("sprites/kirby/Class_Normal.png", "Kirby"));
	//kirby->physicsLayer = (int)PhysicsLayer::Player;
	//kirby->sortLayer = 1;
	//kirby->SetPosition({ -80.0f, 0.0f });
	
	Kirby* kirby = (Kirby*)FindGameObject("Kirby");
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

	CameraPointer* tempCamPtr1 = (CameraPointer*)AddGameObject(new CameraPointer("tempCamPtr"));
	tempCamPtr1->SetSize({ 80.0f * 2.0f, size.y });
	tempCamPtr1->physicsLayer = (int)PhysicsLayer::Ground;
	tempCamPtr1->SetOrigin(Origins::MC);
	tempCamPtr1->SetType(CameraType::Fixed);
	tempCamPtr1->SetPosition({ 0.0f, 0.0f });
	tempCamPtr1->SetTarget(kirby);
	BoxCollider* camCol1 = (BoxCollider*)tempCamPtr1->AddComponent(new BoxCollider(*tempCamPtr1));
	camCol1->SetTrigger(true);

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

	RectangleShapeGO* tempTiltedGround5 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	tempTiltedGround5->AddTag("Ground");
	tempTiltedGround5->SetSize({ 24.0f, 24.0f });
	tempTiltedGround5->physicsLayer = (int)PhysicsLayer::Ground;
	tempTiltedGround5->SetOrigin(Origins::MC);
	//tempGround2->SetPosition({ 0.0f, 100.0f });
	tempTiltedGround5->SetPosition({ 12.0f, 70.0f - 5.0f });
	BoxCollider* boxCol5 = (BoxCollider*)tempTiltedGround5->AddComponent(new BoxCollider(*tempTiltedGround5));

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
	//case CameraType::Horizontal:
	//	targetPoint = { kirby->GetPosition().x, worldView.getCenter().y };
	//	break;
	//case CameraType::Vertical:
	//	targetPoint = { worldView.getCenter().x, kirby->GetPosition().y };
	//	break;
	case CameraType::Fixed:
		targetPoint = worldView.getCenter();
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

	if (Input.GetKeyDown(Keyboard::F5))
	{
		Mob* suctionAble = (Mob*)AddGameObject(new Mob((KirbyAbility)0, "sprites/mob/mob_normal.png", "Suctionable"));
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
		Cutter* suctionAble = (Cutter*)AddGameObject(new Cutter((KirbyAbility)1, "sprites/mob/mob_Cutter.png", "Cutter"));
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
		Mob* suctionAble = (Mob*)AddGameObject(new Mob((KirbyAbility)2, "sprites/mob/Mob_Beam.png", "Suctionable"));
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
		Mob* suctionAble = (Mob*)AddGameObject(new Mob((KirbyAbility)3, "sprites/mob/mob_Bomb.png", "Suctionable"));
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

	Json::Value playerNode = rootNode["Player"];
	Json::Value itemNodes = rootNode["Item"];
	Json::Value enemyNodes = rootNode["Enemy"];
	Json::Value doorNodes = rootNode["Door"];
	Json::Value groundNodes = rootNode["Ground"];
	Json::Value cameraNodes = rootNode["Camera"];
	Json::Value ambientObjectNodes = rootNode["AmbientObject"];
	sf::Vector2f cellSize = { 24.0f, 24.0f };

	Kirby* kirby = (Kirby*)AddGameObject(new Kirby("sprites/kirby/Class_Normal.png", "Kirby"));
	kirby->physicsLayer = (int)PhysicsLayer::Player;
	kirby->sortLayer = playerNode["SortLayer"].asInt();
	kirby->SetPosition({ playerNode["Position"]["x"].asFloat(), playerNode["Position"]["y"].asFloat() });

	for (int i = 0; i < itemNodes.size(); i++)
	{
		Json::Value node = itemNodes[i];
		ItemType type = (ItemType)node["Type"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		std::string textureId = "sprites/item/items.png";
		sf::IntRect rect;
		int sortLayer = node["SortLayer"].asInt();
		switch (type)
		{
		case ItemType::Life:
			rect = { 216, 0, 24, 24};
			break;
		case ItemType::God:
			rect = { 216, 24, 24, 24 };
			break;
		case ItemType::MaxTomato:
			rect = { 120, 24, 24, 24 };
			break;
		case ItemType::Normal:
			rect = { 96, 24, 24, 24 };
			break;
		}
		SpriteGO* item = (SpriteGO*)AddGameObject(new SpriteGO(textureId, "item"));
		item->sprite.setTextureRect(rect);
		item->SetSize(cellSize);
		item->physicsLayer = (int)PhysicsLayer::Ground;
		item->sortLayer = sortLayer;
		item->SetPosition(position);
	}

	for (int i = 0; i < enemyNodes.size(); i++)
	{
		Json::Value node = enemyNodes[i];
		EnemyType type = (EnemyType)node["Type"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		int sortLayer = node["SortLayer"].asInt();

		switch (type)
		{
		case EnemyType::Cutter:
		{
			Cutter* suctionAble = (Cutter*)AddGameObject(new Cutter((KirbyAbility)1, "sprites/mob/mob_Cutter.png", "Cutter"));
			suctionAble->AddTag("Suctionable");
			suctionAble->AddTag("Mob");
			suctionAble->SetSize(cellSize); //
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

			suctionAble->SetOrigin({ 36.0f, 48.0f });
			suctionAble->SetPosition(position); //
			suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
			suctionAbleCol->SetOffset({ -12.0f, -24.0f });
		}
			break;
		case EnemyType::Beam:
			break;
		case EnemyType::Bomb:
			break;
		case EnemyType::Bear:
			break;
		case EnemyType::Chick:
			break;
		case EnemyType::Fly:
			break;
		case EnemyType::Mushroom:
			break;
		case EnemyType::Normal:
		{
			//Mob* suctionAble = (Mob*)AddGameObject(new Mob((KirbyAbility)0, "sprites/mob/mob_normal.png", "Suctionable"));
			//suctionAble->AddTag("Suctionable");
			//suctionAble->AddTag("Mob");
			//suctionAble->SetSize(cellSize); //
			//suctionAble->physicsLayer = (int)PhysicsLayer::Enemy;
			//suctionAble->SetPosition(position);
			//BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
			//RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
			//suctionAbleCol->SetRigidbody(rig);
			//Animator* ani = (Animator*)suctionAble->AddComponent(new Animator(*suctionAble, "animations/Mob/Normal/Normal", "Move"));
			//suctionAble->SetAnimator(ani);
			//suctionAble->SetRigidBody(rig);

			//suctionAble->SetOrigin({ 36.0f, 48.0f });
			//suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
			//suctionAbleCol->SetOffset({ -12.0f, -24.0f });
		}
			break;
		case EnemyType::SubBoss:
			break;
		case EnemyType::Boss:
			break;
		}
	}

	for (int i = 0; i < doorNodes.size(); i++)
	{
		Json::Value node = doorNodes[i];
		DoorType type = (DoorType)node["Type"].asInt();
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() - 24.0f };
		sf::Vector2f movePosition = { node["MovePosition"]["x"].asFloat(), node["MovePosition"]["y"].asFloat()};
		int sortLayer = node["SortLayer"].asInt();

		Door* tempDoor = (Door*)AddGameObject(new Door("sprites/temp/Door.png", "Door"));
		tempDoor->physicsLayer = (int)PhysicsLayer::Interact;
		tempDoor->SetPosition(position);
		tempDoor->SetMovePosition(movePosition);
		BoxCollider* doorCol = (BoxCollider*)tempDoor->AddComponent(new BoxCollider(*tempDoor));
		doorCol->SetTrigger(true);
		doorCol->SetRect({ 0.0f, 0.0f, 24.0f, 48.0f });
	}

	for (int i = 0; i < groundNodes.size(); i++)
	{
		Json::Value node = groundNodes[i];
		Ground* ground = (Ground*)AddGameObject(new Ground(rootNode["Path"].asString(), "ground"));
		ground->SetData(node);
		ground->SetGroundType((GroundType)node["Type"].asInt());
	}

	for (int i = 0; i < cameraNodes.size(); i++)
	{
		Json::Value node = cameraNodes[i];
		CameraType type = (CameraType)node["Type"].asInt();
		if (type == CameraType::MapStart)
		{
			type = CameraType::Free;
		}
		sf::Vector2f position = { node["Position"]["x"].asFloat(), node["Position"]["y"].asFloat() };
		sf::Vector2f size;
		size.x = node["EndPosition"]["x"].asFloat() - node["Position"]["x"].asFloat() + cellSize.x;
		size.y = node["EndPosition"]["y"].asFloat() - node["Position"]["y"].asFloat() + cellSize.y;

		CameraPointer* camPtr = (CameraPointer*)AddGameObject(new CameraPointer("camPtr"));
		camPtr->SetSize(size);
		camPtr->physicsLayer = (int)PhysicsLayer::Ground;
		camPtr->SetType(type);
		camPtr->SetPosition(position);
		camPtr->SetTarget(kirby);

		BoxCollider* camCol = (BoxCollider*)camPtr->AddComponent(new BoxCollider(*camPtr));
		camCol->SetTrigger(true);
	}

	for (int i = 0; i < ambientObjectNodes.size(); i++)
	{
		Json::Value node = ambientObjectNodes[i];
	}
}