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

	Controller* testController = (Controller*)AddGameObject(new Controller(*kirby, "Controller"));

	RectangleShapeGO* tempGround = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Ground"));
	tempGround->SetSize({ 106.0f, 20.0f });
	tempGround->physicsLayer = (int)PhysicsLayer::Ground;
	tempGround->SetOrigin(Origins::MC);
	tempGround->SetPosition({ 0.0f, 100.0f });
	BoxCollider* boxCol = (BoxCollider*)tempGround->AddComponent(new BoxCollider(*tempGround));
	//boxCol->SetRotationOffset(30.0f);

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
