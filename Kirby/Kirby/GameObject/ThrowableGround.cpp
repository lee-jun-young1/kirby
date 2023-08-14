#include "stdafx.h"
#include "ThrowableGround.h"


void ThroughtableGround::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetPosition().y > position.y + size.y)
	{
		collider->SetTrigger(true);
	}
}

void ThroughtableGround::OnTriggerEnter(Collider* col)
{
	if (col->GetGameObject().GetPosition().y < (position.y + 1.0f))
	{
		collider->SetTrigger(false);
	}
}


void ThroughtableGround::OnTriggerExit(Collider* col)
{
	if (col->GetGameObject().GetPosition().y < position.y)
	{
		collider->SetTrigger(false);
	}
}
