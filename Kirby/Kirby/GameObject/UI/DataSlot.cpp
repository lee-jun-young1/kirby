#include "stdafx.h"
#include "DataSlot.h"

void DataSlot::Reset()
{
	SpriteGO::Reset();
	SetScale({0.81f, 0.80f});
}

void DataSlot::Update(float deltaTime)
{
	if (active)
	{
		switch (moveDirection)
		{
		case DataSlot::Direction::Up:
			MoveUp(deltaTime);
			break;
		case DataSlot::Direction::Down:
			MoveDown(deltaTime);
			break;
		}
	}
}

void DataSlot::MoveUp(float deltaTime)
{
	if (position.y <= 0.0f)
	{
		active = false;
		return;
	}
	SetPosition(position.x, position.y += (-1 * speed) * deltaTime);
}

void DataSlot::MoveDown(float deltaTime)
{
	if (position.y >= 0.0f)
	{
		active = false;
		return;
	}
	SetPosition(position.x, position.y += speed * deltaTime);
}
