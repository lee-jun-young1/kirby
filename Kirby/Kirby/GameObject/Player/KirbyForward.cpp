#include "stdafx.h"
#include "KirbyForward.h"
#include <Kirby.h>

void KirbyForward::Update(float dt)
{
	SetPosition(kirby->GetPosition());
}

void KirbyForward::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Suctionable"))
	{
		kirby->AddNearUnit(&col->GetGameObject());
	}
}

void KirbyForward::OnTriggerExit(Collider* col)
{
	if (col->GetGameObject().HasTag("Suctionable"))
	{
		kirby->RemoveNearUnit(&col->GetGameObject());
	}
}
