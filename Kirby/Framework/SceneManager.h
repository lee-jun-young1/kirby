#pragma once
#include "Scene.h"
#include "Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
protected:
	SceneManager() = default;
	virtual ~SceneManager() override = default;

	std::vector<Scene*> scenes;
	SceneId currentSceneId = SceneId::None;
	Scene* currentScene;

	SceneId startSceneId = SceneId::Title;

public:
	void ChangeScene(SceneId id);

	void Init();
	void Release();
	
	void UpdateComponent(float deltaTime);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnGUI(sf::RenderWindow& window);

	Scene* GetCurrentScene() const;
};
#define SCENE_MANAGER (SceneManager::GetInstance())