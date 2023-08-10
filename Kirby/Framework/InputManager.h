#pragma once
#include "stdafx.h"
#include "Singleton.h"
using namespace std;
using namespace sf;

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	std::list<int> positives;
	std::list<int> negatives;
	
	float sensi = 1.0f;
	float value = 0.0f;
};

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;
protected:
	InputManager();
	virtual ~InputManager() = default;

	std::list<int> downList;
	std::list<int> ingList;
	std::list<int> upList;

	sf::Vector2f mousePosition;
	float scrollDelta;

	std::map<Axis, AxisInfo> axisInfoMap;
public:

	void Init();
	void Update(float deltaTime);
	void UpdateEvent(const Event& event);

	bool GetKeyDown(Keyboard::Key key);
	bool GetKey(Keyboard::Key key);
	bool GetKeyUp(Keyboard::Key key);

	const sf::Vector2f& GetMousePosition();
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetMouseButton(sf::Mouse::Button button);
	bool GetMouseButtonUp(sf::Mouse::Button button);

	float GetMouseScrollDelta();

	float GetAxis(Axis axis);
	float GetAxisRaw(Axis axis);
};

#define Input (InputManager::GetInstance())