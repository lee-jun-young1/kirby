#include "stdafx.h"
#include "ClearItem.h"
#include "Kirby.h"

void ClearItem::OnCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Kirby")
	{
		kirby->StageClear();
		SetActive(false);
	}
}
