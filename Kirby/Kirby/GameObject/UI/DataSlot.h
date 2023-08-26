#pragma once
#include "SpriteGO.h"
class DataSlot : public SpriteGO
{
public:
	enum class Direction
	{
		None = -1,
		Up,
		Down
	};
protected:
	Direction moveDirection = Direction::None;
	bool active = false;
	float speed = 500.0f;

public:
	DataSlot(const std::string textureID = "", const std::string& name = "") : SpriteGO(textureID, name) {}
	
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;

	void SetMoveDirection(Direction direction) { this->moveDirection = direction; }
	void SetMoveActive(bool active) { this->active = active; }

	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
};

