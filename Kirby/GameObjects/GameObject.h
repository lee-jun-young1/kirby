#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Collider.h"
using namespace std;

class GameObject
{
protected:
	bool isActive = true;//true : Run Update(), Draw()

	string name;

	sf::Vector2f position;

	sf::Vector2f size;

	sf::Vector2f origin;

	list<Component*> components;
	GameObject* parent;
public:
	int sortLayer = 0;
	int sortOrder = 0;
	int physicsLayer = 0;

	bool IsActive() const;
	void SetActive(bool active);

	void SetParent(GameObject* parent) { this->parent = parent; }
	GameObject* GetParent() { return parent; }

	string GetName();
	virtual void SetName(const std::string& name);

	sf::Vector2f GetPosition();
	virtual void SetPosition(const sf::Vector2f& position);

	virtual void SetPosition(const float& x, const float& y);

	virtual void SetOrigin(const Origins& origin) = 0;
	virtual void SetOrigin(const sf::Vector2f& origin);
	const sf::Vector2f& GetOrigin() { return origin; };

	virtual void SetSize(const sf::Vector2f& size) { this->size = size; }
	const sf::Vector2f& GetSize() { return size; };

	virtual void Init() {};
	virtual void Release() {};

	virtual void Reset(); //√ ±‚»≠

	virtual void UpdateComponent(float dt);

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnGUI(sf::RenderWindow& window);

	GameObject(const std::string& name = "");
	virtual ~GameObject();

	Component* GetComponent(const ComponentType type);
	void GetComponents(std::list<Component*>& list, const ComponentType type);
	bool Exist(Component* component);
	Component* AddComponent(Component* component);
	void RemoveGameObject(Component* component);

	virtual void OnCollisionEnter(Collider* col) {};
	virtual void OnCollisionStay(Collider* col) {};
	virtual void OnCollisionExit(Collider* col) {};
	virtual void OnTriggerEnter(Collider* col) {};
	virtual void OnTriggerStay(Collider* col) {};
	virtual void OnTriggerExit(Collider* col) {};
};