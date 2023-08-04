#pragma once
#include "stdafx.h"
#include "Collider.h"
#include "Singleton.h"
class PhysicsManager : public Singleton<PhysicsManager>
{
	friend Singleton<PhysicsManager>;
protected:
	PhysicsManager();
	virtual ~PhysicsManager() override = default;
	std::vector<std::list<Collider*>> colliders;
	std::vector<int> layerCollide;
public:
	std::list<Collider*> GetColliders(const int& physicsLayer);
	void AddColliders(Collider* col, const int& physicsLayer);
	void RemoveColliders(Collider* col, const int& physicsLayer);
	void Clear();
};

#define Physics (PhysicsManager::GetInstance())