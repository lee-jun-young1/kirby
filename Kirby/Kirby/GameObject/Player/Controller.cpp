#include "stdafx.h"
#include "Controller.h"
#include <InputManager.h>

void Controller::Init()
{
	GameObject::Init();

	function<bool()> dCondition = [this]() { return Input.GetKey(sf::Keyboard::Key::Left) && IsDoubleClicked(sf::Keyboard::Key::Left); };
	function<void(float)> dAction = [this](float deltaTime) { playable.Dash({ -1.0f, 0.0f }, deltaTime); };
	Command* dCommand = new Command(dCondition, dAction, 0);
	AddCommand(dCommand);


	function<bool()> condition = []() { return Input.GetKey(sf::Keyboard::Key::Left); };
	function<void(float)> action = [this](float deltaTime) { playable.Move({ -1.0f, 0.0f }, deltaTime); };
	Command* command = new Command(condition, action, 1);
	AddCommand(command);


	function<bool()> dConditionD = [this]() { return Input.GetKey(sf::Keyboard::Key::Right) && IsDoubleClicked(sf::Keyboard::Key::Right); };
	function<void(float)> dActionD = [this](float deltaTime) { playable.Dash({ 1.0f, 0.0f }, deltaTime); };
	Command* dCommandD = new Command(dConditionD, dActionD, 0);
	AddCommand(dCommandD);


	function<bool()> conditionD = []() { return Input.GetKey(sf::Keyboard::Key::Right); };
	function<void(float)> actionD = [this](float deltaTime) { playable.Move({ 1.0f, 0.0f }, deltaTime); };
	Command* commandD = new Command(conditionD, actionD, 1);
	AddCommand(commandD);

	function<bool()> conditionC = [this]() { return IsContinue(sf::Keyboard::Key::C); };
	function<void(float)> actionC = [this](float deltaTime) { playable.Charge(); };
	Command* commandC = new Command(conditionC, actionC, 1);
	AddCommand(commandC);

	function<bool()> conditionCEnd = [this]() { return Input.GetKeyUp(sf::Keyboard::Key::C); };
	function<void(float)> actionCEnd = [this](float deltaTime) { playable.ChargeEnd(); };
	Command* commandCEnd = new Command(conditionCEnd, actionCEnd, 1);
	AddCommand(commandCEnd);
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
	UpdateKeyTime(dt);
	CheckCommand(dt);
}

void Controller::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Controller::OnGUI(sf::RenderWindow& window)
{
	GameObject::OnGUI(window);
}

void Controller::UpdateKeyTime(float dt)
{
	for (int i = 0; i < Keyboard::KeyCount; i++)
	{
		if (Input.GetKeyDown((Keyboard::Key)i))
		{
			keyDownList.push_back({ (Keyboard::Key)i });
		}
		if (Input.GetKeyUp((Keyboard::Key)i))
		{
			keyUpList.push_back({ (Keyboard::Key)i });
		}
	}
	for (auto it = keyDownList.begin(); it != keyDownList.end(); it++)
	{
		it->time += dt;
		if (Input.GetKeyUp(it->keyCode))
		{
			it = keyDownList.erase(it);
			if (it == keyDownList.end())
			{
				break;
			}
		}
	}
	for (auto it = keyUpList.begin(); it != keyUpList.end(); it++)
	{
		it->time += dt;
		if (it->time > keyContinueTime)
		{
			it = keyUpList.erase(it);
			if (it == keyUpList.end())
			{
				break;
			}
		}
	}
}

const bool& Controller::IsDoubleClicked(const sf::Keyboard::Key& keyCode)
{
	for (auto it = keyUpList.begin(); it != keyUpList.end(); it++)
	{
		if (it->keyCode == keyCode)
		{
			it->time = 0.0f;
			return true;
		}
	}
	return false;
}

const bool& Controller::IsContinue(const sf::Keyboard::Key& keyCode)
{
	for (auto it = keyDownList.begin(); it != keyDownList.end(); it++)
	{
		if (it->keyCode == keyCode)
		{
			return it->time > keyContinueTime;
		}
	}
	return false;
}

void Controller::CheckCommand(float deltaTime)
{
	for (auto command : commandList)
	{
		if (command->CheckCondition(deltaTime))
		{
			break;
		}
	}
}

void Controller::AddCommand(Command* command)
{
	auto it = commandList.begin();
	while (it != commandList.end())
	{
		if (*it == command)
		{
			return;
		}
		it++;
	}
	commandList.push_back(command);

	OrderCommand();
}

void Controller::RemoveCommand(Command* command)
{
	auto it = commandList.begin();
	while (it != commandList.end())
	{
		if (*it == command)
		{
			commandList.remove(command);
			return;
		}
		it++;
	}
}

void Controller::OrderCommand()
{
	commandList.sort([](Command* lhs, Command* rhs) {
		return lhs->GetOrder() < rhs->GetOrder();
		});
}