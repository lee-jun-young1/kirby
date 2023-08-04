#pragma once
class GameObject;

class Component
{
protected:
	bool isEnable = true;
	GameObject& gameObject;
	ComponentType componentType;
	bool isUnique;
public:
	virtual bool IsEnable();
	virtual void SetEnable(bool isEnable);
	bool IsUnique();
	ComponentType GetComponentType();

	GameObject& GetGameObject();

	Component(GameObject& gameObject, ComponentType type, bool isUnique);

	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Release() = 0;
	virtual void OnGUI(sf::RenderWindow& window) {};

	virtual void OnGameObjectEnable() = 0;
	virtual void OnGameObjectDisable() = 0;
};

