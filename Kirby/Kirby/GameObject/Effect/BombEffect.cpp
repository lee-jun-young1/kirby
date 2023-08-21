#include "stdafx.h"
#include "BombEffect.h"

void BombEffect::Update(float deltaTime)
{
}

void BombEffect::OnCollisionEnter(Collider* col)
{
	col->GetGameObject().HasTag("Hitable");
}
