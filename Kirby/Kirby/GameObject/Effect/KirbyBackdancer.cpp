#include "stdafx.h"
#include "KirbyBackdancer.h"
#include "Animator.h"

void KirbyBackdancer::Init()
{
	SpriteGO::Init();
	AddComponent(new Animator(*this, "animations/Kirby/Kirby", "Dance"));
}

void KirbyBackdancer::Update(float dt)
{
	SpriteGO::Update(dt);
	SetPosition(kirby->GetPosition() + offset);

	cout << GetPosition().x << endl;
}