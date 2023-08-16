#include "stdafx.h"
#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	for (int i = 0; i < (int)PhysicsLayer::Count; i++)
	{
		layerCollide.push_back(0);
		colliders.push_back(std::list<Collider*>());
	}
	AddCollideLayer(PhysicsLayer::Ground, PhysicsLayer::Player);
	AddCollideLayer(PhysicsLayer::Ground, PhysicsLayer::PlayerEffect);
	AddCollideLayer(PhysicsLayer::Ground, PhysicsLayer::Enemy);
	AddCollideLayer(PhysicsLayer::Ground, PhysicsLayer::EnemyEffect);
	AddCollideLayer(PhysicsLayer::Ground, PhysicsLayer::Item);
	AddCollideLayer(PhysicsLayer::Ground, PhysicsLayer::AbilityItem);

	AddCollideLayer(PhysicsLayer::Player, PhysicsLayer::PlayerEffect);
	AddCollideLayer(PhysicsLayer::Player, PhysicsLayer::Enemy);
	AddCollideLayer(PhysicsLayer::Player, PhysicsLayer::EnemyEffect);
	AddCollideLayer(PhysicsLayer::Player, PhysicsLayer::Item);

	AddCollideLayer(PhysicsLayer::PlayerEffect, PhysicsLayer::Enemy);
	AddCollideLayer(PhysicsLayer::PlayerEffect, PhysicsLayer::Item);

	AddCollideLayer(PhysicsLayer::Enemy, PhysicsLayer::EnemyEffect);
}

std::list<Collider*> PhysicsManager::GetColliders(const int& physicsLayer)
{
	std::list<Collider*> result;
	for (int i = 0; i < (int)PhysicsLayer::Count; i++)
	{
		if (layerCollide[physicsLayer] & (1 << i) && colliders[i].size() > 0)
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

void PhysicsManager::AddCollideLayer(PhysicsLayer a, PhysicsLayer b)
{
	int targetBit = 1 << (int)b;
	layerCollide[(int)a] = layerCollide[(int)a] | targetBit;
	std::cout << (int)a << " = " << layerCollide[(int)a] << std::endl;
	targetBit = 1 << (int)a;
	layerCollide[(int)b] = layerCollide[(int)b] | targetBit;
	std::cout << (int)b << " = " << layerCollide[(int)b] << std::endl;
}

void PhysicsManager::RemoveCollideLayer(PhysicsLayer a, PhysicsLayer b)
{
	int targetBit = 1 << (int)b;
	layerCollide[(int)a] = layerCollide[(int)a] ^ targetBit;
	targetBit = 1 << (int)a;
	layerCollide[(int)b] = layerCollide[(int)b] ^ targetBit;
}