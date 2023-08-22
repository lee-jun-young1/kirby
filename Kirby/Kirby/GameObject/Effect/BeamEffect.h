#pragma once
#include "SpriteGO.h"
class EffectPool;
class BeamEffect : public SpriteGO
{
public:
	enum class Mode
	{
		Whip,
		Ball,
	};
protected:
	Mode mode = Mode::Whip;

	EffectPool* pool;
	BeamEffect* prevNode;
	sf::Vector2f effectDirection;
	float effectRotation = -20.0f;
	float time = 0.0f;
public:
	BeamEffect(const std::string textureID = "sprites/effects/Beam_Effect.png", const std::string& name = "BeamEffect") 
		:SpriteGO(textureID, name) {};
	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(Collider* col) override;
	const float& GetTotalRotation() const;
	void SetEffectDirection(const sf::Vector2f& effectDirection) { this->effectDirection = effectDirection; }
	void SetEffectRotation(const float& effectRotation) { this->effectRotation = effectRotation; }
	void SetPrevNode(BeamEffect* prevNode) { this->prevNode = prevNode; }
	void SetPool(EffectPool* pool) { this->pool = pool; }
	void SetMode(const Mode& mode) { this->mode = mode; }
};

