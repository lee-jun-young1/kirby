#include "stdafx.h"
#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	for (int i = 0; i < (int)PhysicsLayer::Count; i++)
	{
		layerCollide.push_back(0);
		colliders.push_back(std::list<Collider*>());
	}
	layerCollide[1] += 1 << 3;

	layerCollide[2] += 1 << 3;

	layerCollide[3] += 1 << 1;
	layerCollide[3] += 1 << 2;
	layerCollide[3] += 1 << 4;
	layerCollide[3] += 1 << 5;

	layerCollide[4] += 1 << 3;

	layerCollide[5] += 1 << 3;
}

std::list<Collider*> PhysicsManager::GetColliders(const int& physicsLayer)
{
	std::list<Collider*> result;
	for (int i = 0; i < (int)PhysicsLayer::Count; i++)
	{
		if (layerCollide[physicsLayer] & 1 << i && colliders[i].size() > 0)
		{
			auto it = colliders[i].begin();
			while (it != colliders[i].end())
			{
				result.push_back(*it);
				it++;
			}
		}
	}
	return result;
}

void PhysicsManager::AddColliders(Collider* col, const int& physicsLayer)
{
	auto it = colliders[physicsLayer].begin();
	for(it; it != colliders[physicsLayer].end(); it++)
	{
		if (*it == col)
		{
			return;
		}
	}
	colliders[physicsLayer].push_back(col);
}

void PhysicsManager::RemoveColliders(Collider* col, const int& physicsLayer)
{
	colliders[physicsLayer].remove(col);
}

void PhysicsManager::Clear()
{
	for (int i = 0; i < (int)PhysicsLayer::Count; i++)
	{
		colliders[i].clear();
	}
}
