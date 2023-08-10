#pragma once
#include <Playable.h>

struct KeyInfo
{
	sf::Keyboard::Key keyCode;
	float time;
};

class Command
{
protected:
	std::function<bool()> condition;
	std::function<void(float)> action;
	const int order;
public:
	Command(std::function<bool()>& condition, std::function<void(float)>& action, const int& commandOrder = 0) : 
		order(commandOrder), condition(condition), action(action) {};

	const int& GetOrder() { return order; }
	bool CheckCondition(float deltaTime) { if (condition()) { action(deltaTime); return true; } return false; }
};

class Controller : public GameObject
{
protected:
	Playable& playable;

	list<KeyInfo> keyDownList;
	list<KeyInfo> keyUpList;

	list<Command*> commandList;

	float keyContinueTime = 0.2f;
public:
	Controller(Playable& playable, const string& name = "") : GameObject(name), playable(playable) {}
	//Controller(const string& name = "") : GameObject(name), playable(playable) {}

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void UpdateComponent(float dt) override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void OnGUI(sf::RenderWindow& window) override;

	virtual void UpdateKeyTime(float dt); 

	const bool& IsDoubleClicked(const sf::Keyboard::Key& keyCode);
	const bool& IsContinue(const sf::Keyboard::Key& keyCode);

	virtual void CheckCommand(float deltaTime);
	virtual void AddCommand(Command* command);
	virtual void RemoveCommand(Command* command);
	virtual void OrderCommand();
};