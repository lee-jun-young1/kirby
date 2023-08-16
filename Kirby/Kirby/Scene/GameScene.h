#pragma once
#include "Scene.h"
class RectangleShapeGO;
class GameScene : public Scene
{
protected:

public:
	GameScene();
	virtual ~GameScene();

	virtual void Enter() override;

	// Scene��(��) ���� ��ӵ�
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

