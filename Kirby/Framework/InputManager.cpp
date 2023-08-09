#include "stdafx.h"
#include "InputManager.h"
#include <algorithm>
#include "Framework.h"
#include <Utils.h>


InputManager::InputManager()
{
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positives.push_back((int)sf::Keyboard::Key::D);
	infoH.positives.push_back((int)sf::Keyboard::Key::Right);
	infoH.negatives.push_back((int)sf::Keyboard::Key::A);
	infoH.negatives.push_back((int)sf::Keyboard::Key::Left);
	infoH.sensi = 2.0f;
	axisInfoMap.insert({infoH.axis, infoH});

	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positives.push_back((int)sf::Keyboard::Key::S);
	infoV.positives.push_back((int)sf::Keyboard::Key::Down);
	infoV.negatives.push_back((int)sf::Keyboard::Key::W);
	infoV.negatives.push_back((int)sf::Keyboard::Key::Up);
	infoV.sensi = 2.0f;
	axisInfoMap.insert({ infoV.axis, infoV });
}

void InputManager::Init()
{
}

void InputManager::Update(float deltaTime)
{
	downList.clear();
	upList.clear();

	for (auto& it : axisInfoMap)
	{
		auto& axisInfo = it.second;
		float raw = GetAxisRaw(axisInfo.axis);
		if (raw == 0.0f && axisInfo.value != 0.0f)
		{
			raw = axisInfo.value > 0.0f ? -1.0f : 1.0f;
		}

		float diff = axisInfo.sensi * deltaTime;
		axisInfo.value = Utils::Clamp(axisInfo.value + raw * diff, -1.0f, 1.0f);
		if (abs(axisInfo.value) < diff * 0.5f)
			axisInfo.value = 0.0f;
	}
	wheelMovement = 0.f;
}

void InputManager::UpdateEvent(const sf::Event& event)
{

	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			downList.push_back(event.key.code);
			ingList.push_back(event.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		ingList.remove(event.key.code);
		upList.push_back(event.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		if (!GetMouseButton(event.mouseButton.button))
		{
			downList.push_back(Keyboard::KeyCount + event.mouseButton.button);
			ingList.push_back(Keyboard::KeyCount + event.mouseButton.button);
		}
		break;
	case sf::Event::MouseButtonReleased:
		ingList.remove(Keyboard::KeyCount + event.mouseButton.button);
		upList.push_back(Keyboard::KeyCount + event.mouseButton.button);
		break;
	case sf::Event::MouseWheelScrolled:
		wheelMovement = event.mouseWheelScroll.delta;
	}

	mousePosition = (sf::Vector2f)sf::Mouse::getPosition(FRAMEWORK.GetWindow());
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upList.begin(), upList.end(), key) != upList.end();
}

const sf::Vector2f& InputManager::GetMousePosition()
{
	return mousePosition;
}

bool InputManager::GetMouseButtonDown(sf::Mouse::Button button)
{
	int code = Keyboard::KeyCount + button;
	return std::find(downList.begin(), downList.end(), code) != downList.end();
}

bool InputManager::GetMouseButton(sf::Mouse::Button button)
{
	int code = Keyboard::KeyCount + button;
	return std::find(ingList.begin(), ingList.end(), code) != ingList.end();
}

bool InputManager::GetMouseButtonUp(sf::Mouse::Button button)
{
	int code = Keyboard::KeyCount + button;
	return std::find(upList.begin(), upList.end(), code) != upList.end();
}

float InputManager::GetMouseWheelMovement()
{
	return wheelMovement;
}

float InputManager::GetAxis(Axis axis)
{
	const auto& it = axisInfoMap.find(axis);
	if (it == axisInfoMap.end())
		return 0.0f;

	const AxisInfo& info = it->second;

	return info.value;
}

float InputManager::GetAxisRaw(Axis axis)
{
	const auto& it = axisInfoMap.find(axis);
	if (it == axisInfoMap.end())
		return 0.0f;

	const AxisInfo& info = it->second;

	auto rit = ingList.rbegin();

	while (rit != ingList.rend())
	{
		int code = *rit;
		if (std::find(info.positives.begin(), info.positives.end(), code) != info.positives.end())
		{
			return 1.0f;
		}
		if (std::find(info.negatives.begin(), info.negatives.end(), code) != info.negatives.end())
		{
			return -1.0f;
		}
		++rit;
	}

	return 0.0f;
}
