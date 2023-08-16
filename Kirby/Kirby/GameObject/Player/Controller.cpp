#include "stdafx.h"
#include "Controller.h"
#include <InputManager.h>

void Controller::Init()
{
	GameObject::Init();

	function<bool()> dCondition = [this]() { return Input.GetKeyDown(sf::Keyboard::Key::Left) && IsDoubleClicked(sf::Keyboard::Key::Left); };
	function<void(float)> dAction = [this](float deltaTime) { playable.DashKey( -1.0f ); };
	Command* dCommand = new Command(dCondition, dAction, 0);
	AddCommand(dCommand);


	function<bool()> condition = []() { return Input.GetKeyDown(sf::Keyboard::Key::Left); };
	function<void(float)> action = [this](float deltaTime) { playable.MoveKey( -1.0f ); };
	Command* command = new Command(condition, action, 1);
	AddCommand(command);


	function<bool()> dConditionD = [this]() { return Input.GetKeyDown(sf::Keyboard::Key::Right) && IsDoubleClicked(sf::Keyboard::Key::Right); };
	function<void(float)> dActionD = [this](float deltaTime) { playable.DashKey( 1.0f ); };
	Command* dCommandD = new Command(dConditionD, dActionD, 0);
	AddCommand(dCommandD);


	function<bool()> conditionD = []() { return Input.GetKeyDown(sf::Keyboard::Key::Right); };
	function<void(float)> actionD = [this](float deltaTime) { playable.MoveKey( 1.0f ); };
	Command* commandD = new Command(conditionD, actionD, 1);
	AddCommand(commandD);

	function<bool()> conditionMoveUp = []() { return Input.GetKeyUp(sf::Keyboard::Key::Left) || Input.GetKeyUp(sf::Keyboard::Key::Right); };
	function<void(float)> actionMoveUp = [this](float deltaTime) { playable.MoveKeyEnd(); };
	Command* commandMoveUp = new Command(conditionMoveUp, actionMoveUp, 1);
	AddCommand(commandMoveUp);

	function<bool()> conditionCDown = [this]() { return Input.GetKeyDown(sf::Keyboard::Key::X); };
	function<void(float)> actionCDown = [this](float deltaTime) { playable.ChargeKey(); };
	Command* commandCDown = new Command(conditionCDown, actionCDown, 1);
	AddCommand(commandCDown);

	function<bool()> conditionC = [this]() { return IsContinue(sf::Keyboard::Key::X); };
	function<void(float)> actionC = [this](float deltaTime) { playable.ChargeKeyContinue(); };
	Command* commandC = new Command(conditionC, actionC, 1);
	AddCommand(commandC);

	function<bool()> conditionCEnd = [this]() { return Input.GetKeyUp(sf::Keyboard::Key::X); };
	function<void(float)> actionCEnd = [this](float deltaTime) { playable.ChargeKeyEnd(); };
	Command* commandCEnd = new Command(conditionCEnd, actionCEnd, 1);
	AddCommand(commandCEnd);

	function<bool()> conditionDoor = [this]() { return Input.GetKeyDown(sf::Keyboard::Key::Up); };
	function<void(float)> actionDoor = [this](float deltaTime) { playable.DoorKey(); };
	Command* commandDoor = new Command(conditionDoor, actionDoor, 1);
	AddCommand(commandDoor);

	function<bool()> conditionDoorEnd = [this]() { return Input.GetKeyUp(sf::Keyboard::Key::Up); };
	function<void(float)> actionDoorEnd = [this](float deltaTime) { playable.DoorKeyEnd(); };
	Command* commandDoorEnd = new Command(conditionDoorEnd, actionDoorEnd, 1);
	AddCommand(commandDoorEnd);

	function<bool()> conditionSit = [this]() { return Input.GetKey(sf::Keyboard::Key::Down); };
	function<void(float)> actionSit = [this](float deltaTime) { playable.SitKey(); };
	Command* commandSit = new Command(conditionSit, actionSit, 1);
	AddCommand(commandSit);

	function<bool()> conditionSitEnd = [this]() { return Input.GetKeyUp(sf::Keyboard::Key::Down); };
	function<void(float)> actionSitEnd = [this](float deltaTime) { playable.SitKeyEnd(); };
	Command* commandSitEnd = new Command(conditionSitEnd, actionSitEnd, 1);
	AddCommand(commandSitEnd);

	function<bool()> conditionJump = [this]() { return Input.GetKeyDown(sf::Keyboard::Key::C); };
	function<void(float)> actionJump = [this](float deltaTime) { playable.JumpKey(); };
	Command* commandJump = new Command(conditionJump, actionJump, 0);
	AddCommand(commandJump);

	function<bool()> conditionV = [this]() { return Input.GetKeyDown(sf::Keyboard::Key::V); };
	function<void(float)> actionV = [this](float deltaTime) { playable.VKey(); };
	Command* commandV = new Command(conditionV, actionV, 0);
	AddCommand(commandV);
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
			//break;
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