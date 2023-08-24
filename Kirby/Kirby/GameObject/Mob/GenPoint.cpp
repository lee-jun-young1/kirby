#include "stdafx.h"
#include "GenPoint.h"
#include "MobPool.h"
#include "Mob.h"
void GenPoint::Reset()
{
	GameObject::Reset();
	inCameraEvent = [this]() {
		if (mob != nullptr)
		{
			return;
		}
		mob = pool->GetMob(type);
		mob->Reset();
		mob->SetPosition(position);
		mob->sortLayer = sortLayer;
		mob->SetActive(true);
		mob->SetGenPoint(this);
	};
}

void GenPoint::MobRemove()
{
	mob->SetActive(false);
	pool->MobReturn(mob);
	mob = nullptr;
}

