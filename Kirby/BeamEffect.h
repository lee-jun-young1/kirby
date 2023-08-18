#pragma once
#include "SpriteGO.h"
class BeamEffect : public SpriteGO
{
protected:
	BeamEffect* nextNode;
	sf::Vector2f direction;
public:
	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(Collider* col) override;
};

