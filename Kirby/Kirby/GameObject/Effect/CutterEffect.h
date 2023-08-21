#pragma once
#include "SpriteGO.h"
class EffectPool;
class CutterEffect : public SpriteGO
{
	EffectPool* pool;
	RigidBody2D* rigidbody;
	float startPower;
	bool turned = false;
	float time = 0.0f;
public:
	CutterEffect(const std::string textureID = "sprites/effects/Cutter_Effect.png", const std::string& name = "CutterEffect")
		:SpriteGO(textureID, name) {};
	virtual void Update(float dt) override;
	virtual void OnTriggerEnter(Collider* col) override;
	void SetRigidbody(RigidBody2D* rig) { rigidbody = rig; }
	void Fire(sf::Vector2f axis);
	void SetPool(EffectPool* pool) { this->pool = pool; }
	void Return(bool forced = false);
};

