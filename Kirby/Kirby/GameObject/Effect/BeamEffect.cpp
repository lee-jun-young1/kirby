#include "stdafx.h"
#include "BeamEffect.h"
#include "Utils.h"

void BeamEffect::Update(float deltaTime)
{
	if (nextNode != nullptr)
	{
		sf::Vector2f pos = direction * GetSize().x;
		pos = Utils::RotateWithPivot({ 0.0f, 0.0f }, pos, direction.x * 30.0f);
		nextNode->SetPosition(GetPosition() + pos);
	}
}

void BeamEffect::OnTriggerEnter(Collider* col)
{
}
