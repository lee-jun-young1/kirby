#include "stdafx.h"
#include "MushroomHead.h"
#include <Kirby/GameObject/Player/Playable.h>

void MushroomHead::OnCollisionEnter(Collider* col)
{
    if (col->GetGameObject().GetName() == "Kirby")
    {
        ((Playable*)&col->GetGameObject())->Damage(10, col->GetGameObject().GetPosition().x < GetPosition().x ? -1.0f : 1.0f);
        SetActive(false);
    }
}
