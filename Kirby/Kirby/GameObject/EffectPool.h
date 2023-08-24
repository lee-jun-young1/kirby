#pragma once
#include "GameObject.h"
#include <CutterEffect.h>
#include "ObjectPool.h"
#include <BeamEffect.h>
#include <BombEffect.h>
#include <WoodEffect.h>

class EffectPool : public GameObject
{
protected:
	ObjectPool<CutterEffect> cutterEffects;
	ObjectPool<BeamEffect> beamEffects;
	ObjectPool<BombEffect> bombEffects;
	ObjectPool<WoodEffect> woodEffects;
public:
	EffectPool(const std::string& name = "") : GameObject(name){};

	CutterEffect* GetCutterEffect(const PhysicsLayer& layer);
	BeamEffect* GetBeamEffect(const PhysicsLayer& layer);
	BombEffect* GetBombEffect(const PhysicsLayer& layer);
	WoodEffect* GetWoodEffect(const PhysicsLayer& layer);

	void ReturnCutterEffect(CutterEffect* effect);
	void ReturnBeamEffect(BeamEffect* effect);
	void ReturnBombEffect(BombEffect* effect);
	void ReturnWoodEffect(WoodEffect* effect);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

