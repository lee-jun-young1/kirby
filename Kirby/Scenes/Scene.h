#pragma once

class GameObject;

class Scene
{
protected:
	SceneId sceneId;
	std::string sceneName;

	std::list<GameObject*> gameObjects;
	std::list<GameObject*> removeGameObjects;

	sf::View worldView;
	sf::View uiView;

	sf::RenderWindow& window;

	std::vector<std::tuple<ResourceTypes, std::string>> resources;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
public:
	Scene(SceneId id = SceneId::None);
	virtual ~Scene();

	GameObject* FindGameObject(const std::string& name);
	void FindGameObjects(std::list<GameObject*>& list, const std::string& name);

	bool Exist(GameObject* gameObject);
	GameObject* AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);

	void SortGameObjects();

	sf::Vector2f ScreenToWorldPosition(sf::Vector2f screenPos);
	sf::Vector2f ScreenToUIPosition(sf::Vector2f screenPos);


	sf::Vector2f WorldPositionToScreen(sf::Vector2f worldPos);
	sf::Vector2f UIPositionToScreen(sf::Vector2f uiPos);

	virtual void Enter();
	virtual void Exit();

	virtual void Init();
	void UpdateComponent(float deltaTime);
	virtual void Release() = 0;
	virtual void Reset() = 0;
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnGUI(sf::RenderWindow& window);
};