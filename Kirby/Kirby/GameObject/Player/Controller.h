#pragma once
#include <Playable.h>
class Controller : GameObject
{
protected:
	Playable& playable;
public:
	Controller(Playable& playable) : playable(playable) {}

	virtual void Init();
	virtual void Release();
	virtual void Reset(); //√ ±‚»≠
	virtual void UpdateComponent(float dt);
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnGUI(sf::RenderWindow& window);
};

