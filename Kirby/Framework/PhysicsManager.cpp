#include "stdafx.h"
#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	for (int i = 0; i < (int)PhysicsLayer::Count; i++)
	{
		layerCollide.push_back(0);
		colliders.push_back(std::list<Collider*>());
	}

#pragma region PhysicsLayerSettings

	layerCollide[(int)PhysicsLayer::Ground] += 1 << (int)PhysicsLayer::Player;
	layerCollide[(int)PhysicsLayer::Ground] += 1 << (int)PhysicsLayer::PlayerEffect;
	layerCollide[(int)PhysicsLayer::Ground] += 1 << (int)PhysicsLayer::Enemy;
	layerCollide[(int)PhysicsLayer::Ground] += 1 << (int)PhysicsLayer::EnemyEffect;
	layerCollide[(int)PhysicsLayer::Ground] += 1 << (int)PhysicsLayer::Item;
	layerCollide[(int)PhysicsLayer::Ground] += 1 << (int)PhysicsLayer::AbilityItem;

	layerCollide[(int)PhysicsLayer::Player] += 1 << (int)PhysicsLayer::Ground;
	layerCollide[(int)PhysicsLayer::Player] += 1 << (int)PhysicsLayer::PlayerEffect;
	layerCollide[(int)PhysicsLayer::Player] += 1 << (int)PhysicsLayer::Enemy;
	layerCollide[(int)PhysicsLayer::Player] += 1 << (int)PhysicsLayer::EnemyEffect;
	layerCollide[(int)PhysicsLayer::Player] += 1 << (int)PhysicsLayer::Item;

	layerCollide[(int)PhysicsLayer::PlayerEffect] += 1 << (int)PhysicsLayer::Ground;
	layerCollide[(int)PhysicsLayer::PlayerEffect] += 1 << (int)PhysicsLayer::Player;
	layerCollide[(int)PhysicsLayer::PlayerEffect] += 1 << (int)PhysicsLayer::Enemy;
	layerCollide[(int)PhysicsLayer::PlayerEffect] += 1 << (int)PhysicsLayer::Item;

	layerCollide[(int)PhysicsLayer::Enemy] += 1 << (int)PhysicsLayer::Ground;
	layerCollide[(int)PhysicsLayer::Enemy] += 1 << (int)PhysicsLayer::Player;
	layerCollide[(int)PhysicsLayer::Enemy] += 1 << (int)PhysicsLayer::PlayerEffect;
	layerCollide[(int)PhysicsLayer::Enemy] += 1 << (int)PhysicsLayer::EnemyEffect;

	layerCollide[(int)PhysicsLayer::EnemyEffect] += 1 << (int)PhysicsLayer::Ground;
	layerCollide[(int)PhysicsLayer::EnemyEffect] += 1 << (int)PhysicsLayer::Player;
	layerCollide[(int)PhysicsLayer::EnemyEffect] += 1 << (int)PhysicsLayer::Enemy;

	layerCollide[(int)PhysicsLayer::Item] += 1 << (int)PhysicsLayer::Ground;
	layerCollide[(int)PhysicsLayer::Item] += 1 << (int)PhysicsLayer::Player;
	layerCollide[(int)PhysicsLayer::Item] += 1 << (int)PhysicsLayer::PlayerEffect;

	layerCollide[(int)PhysicsLayer::AbilityItem] += 1 << (int)PhysicsLayer::Ground;

#pragma endregion

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
