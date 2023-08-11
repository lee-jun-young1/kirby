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
	worldView.setCenter(0.0f, 0.0f);

	uiView.setSize(size);
	uiView.setCenter(screenCenter.x, screenCenter.y);

	Scene::Enter();


	GameObject* star = FindGameObject("Star");
	Animation* starAni = (Animation*)star->GetComponent(ComponentType::Animation);
	starAni->SetClip(Resources.GetAnimationClip("animations/Effect/Star.csv"));
	starAni->Play();

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

	Kirby* kirby = (Kirby*)AddGameObject(new Kirby("sprites/kirby/Class_Normal.png", "Kirby"));
	kirby->physicsLayer = (int)PhysicsLayer::Player;
	kirby->sortLayer = 1;
	
	Suction* suction = (Suction*)AddGameObject(new Suction("Suction"));
	suction->SetKirby(kirby);
	suction->SetActive(false);

	kirby->SetSuction(suction);

	SpriteGO* star = (SpriteGO*)AddGameObject(new SpriteGO("sprites/effects/Star.png", "Star"));
	star->SetActive(false);
	Animation* starAni = (Animation*)star->AddComponent(new Animation(*star));
	RigidBody2D* starRig = (RigidBody2D*)star->AddComponent(new RigidBody2D(*star));

	kirby->SetStarEffect(star);



	//RectangleShapeGO* tempGround1 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	//tempGround1->SetSize({ 24.0f, 24.0f });
	//tempGround1->physicsLayer = (int)PhysicsLayer::Ground;
	//tempGround1->SetOrigin(Origins::BC);
	//tempGround1->SetPosition(kirby->GetPosition() + sf::Vector2f(24.0f, -24.0f));
	//BoxCollider* boxCol1 = (BoxCollider*)tempGround1->AddComponent(new BoxCollider(*tempGround1));

	for (int i = 0; i < 4; i++)
	{
		Mob* suctionAble = (Mob*)AddGameObject(new Mob((KirbyAbility)i, "", "Suctionable"));
		suctionAble->SetSize({ 24.0f, 24.0f });
		suctionAble->physicsLayer = (int)PhysicsLayer::Ground;
		suctionAble->SetOrigin(Origins::BC);
		suctionAble->SetPosition(kirby->GetPosition() + sf::Vector2f(-24.0f + i * 48.0f, 0.0f));
		BoxCollider* suctionAbleCol = (BoxCollider*)suctionAble->AddComponent(new BoxCollider(*suctionAble));
		suctionAbleCol->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		suctionAbleCol->SetOffset({ 0.0f, -24.0f });
		RigidBody2D* rig = (RigidBody2D*)suctionAble->AddComponent(new RigidBody2D(*suctionAble));
		suctionAbleCol->SetRigidbody(rig);
		rig->SetGravity(false);
	}


	Controller* testController = (Controller*)AddGameObject(new Controller(*kirby, "Controller"));

	//RectangleShapeGO* tempGround = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	//tempGround->SetSize({ 106.0f, 20.0f });
	//tempGround->physicsLayer = (int)PhysicsLayer::Ground;
	//tempGround->SetOrigin(Origins::BC);
	//tempGround->SetPosition({ 0.0f, 100.0f });
	//BoxCollider* boxCol = (BoxCollider*)tempGround->AddComponent(new BoxCollider(*tempGround));


	//RectangleShapeGO* tempGround2 = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	//tempGround2->SetSize({ 100.0f, 100.0f });
	//tempGround2->physicsLayer = (int)PhysicsLayer::Ground;
	//tempGround2->SetOrigin(Origins::TC);
	//tempGround2->SetPosition({ 0.0f, 0.0f });
	//BoxCollider* boxCol2 = (BoxCollider*)tempGround2->AddComponent(new BoxCollider(*tempGround2));
	//boxCol2->SetRotationOffset(30.0f);


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
}

void SceneExample::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
