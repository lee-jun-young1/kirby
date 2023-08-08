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

SceneExample::SceneExample() 
	: Scene(SceneId::Title)
{
	sceneName = "TitleScene";
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

	RectangleShapeGO* rectGO = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("Rect"));
	rectGO->SetSize({ 2.0f, 80.0f });
	rectGO->physicsLayer = (int)PhysicsLayer::Player;
	rectGO->SetOrigin(Origins::MC);
	BoxCollider* boxCol = (BoxCollider*)rectGO->AddComponent(new BoxCollider(*rectGO));
	boxCol->SetRotationOffset(30.0f);

	RectangleShapeGO* smallRectGO = (RectangleShapeGO*)AddGameObject(new RectangleShapeGO("SmallRect"));
	smallRectGO->SetSize({ 10.0f, 10.0f });
	smallRectGO->physicsLayer = (int)PhysicsLayer::Ground;
	smallRectGO->SetOrigin(Origins::MC);
	smallRectGO->SetPosition({ -20.0f, -20.0f });
	BoxCollider* smallBoxCol = (BoxCollider*)smallRectGO->AddComponent(new BoxCollider(*smallRectGO));
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

	RectangleShapeGO* rectGO = (RectangleShapeGO*)FindGameObject("Rect");
	rectGO->SetRotation(rectGO->GetRotation() + Input.GetAxisRaw(Axis::Horizontal) * 30.0f * deltaTime);

	CircleShapeGO* circleGO = (CircleShapeGO*)FindGameObject("Circle");
	//circleGO->SetPosition(Utils::RotateWithPivot(rectGO->GetPosition(), circleGO->GetPosition(), 30.0f * deltaTime));
}

void SceneExample::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
