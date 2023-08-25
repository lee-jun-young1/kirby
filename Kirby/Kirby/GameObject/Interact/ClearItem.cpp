#include "stdafx.h"
#include "ClearItem.h"
#include "Kirby.h"

void ClearItem::Init()
{
	SpriteGO::Init();
	physicsLayer = (int)PhysicsLayer::Interact;
	BoxCollider* col = (BoxCollider*)AddComponent(new BoxCollider(*this));
	col->SetRect({ 0.0f, 0.0f, 36.0f, 36.0f });
	col->SetOffset({ 18.0f, 18.0f });

	Animation* ani = (Animation*)GetComponent(ComponentType::Animation);
	if (ani == nullptr)
	{
		Animation* ani = (Animation*)AddComponent(new Animation(*this));
		ani->SetClip(Resources.GetAnimationClip("animations/Item/ClearStar.csv"));
	}
}

void ClearItem::OnEnable()
{
	Animation* ani = (Animation*)GetComponent(ComponentType::Animation);
	ani->Play();
}

void ClearItem::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Kirby")
	{
		Kirby* kirby = (Kirby*)&col->GetGameObject();
		kirby->StageClear();
		SetActive(false);
	}
}
