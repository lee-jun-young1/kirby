#include "stdafx.h"
#include "Controller.h"

void Controller::Init()
{
	GameObject::Init();
}

void Controller::Release()
{
	GameObject::Release();
}

void Controller::Reset()
{
	GameObject::Reset();
}

void Controller::UpdateComponent(float dt)
{
	GameObject::UpdateComponent(dt);
}

void Controller::Update(float dt)
{
	GameObject::Update(dt);
}

void Controller::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Controller::OnGUI(sf::RenderWindow& window)
{
	GameObject::OnGUI(window);
}
