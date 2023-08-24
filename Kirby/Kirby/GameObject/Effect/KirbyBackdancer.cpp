#include "stdafx.h"
#include "KirbyBackdancer.h"
#include "Animator.h"

void KirbyBackdancer::Reset()
{
	SpriteGO::Reset();
	Animation* ani = (Animation*)AddComponent(new Animation(*this));
	ani->SetClip(Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv"));
	ani->Play();
}

void KirbyBackdancer::Update(float dt)
{
	SpriteGO::Update(dt);
	SetPosition(kirby->GetPosition() + offset);
}