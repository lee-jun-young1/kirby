#include "stdafx.h"
#include "WarpStar.h"
#include <Animation.h>


void WarpStar::Reset()
{
	SpriteGO::Reset();
	SetActive(true);
	OnEnable();
}

void WarpStar::OnEnable()
{
	Animation* ani = (Animation*)GetComponent(ComponentType::Animation);
	if (ani == nullptr)
	{
		ani = (Animation*)AddComponent(new Animation(*this));
	}
	ani->SetClip(Resources.GetAnimationClip("animations/Item/WarpStar.csv"));
	ani->Play();
}