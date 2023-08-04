#pragma once


enum class Languages
{
	ENG,
	COUNT,
};


enum class SceneId
{
	None = -1,
	MapTool,
	Title,
	Demo,
	Game,
	Count,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
	SpriteFont,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ComponentType
{
	RigidBody,
	Collider,
	Animation,
	Audio,
};

enum class ColliderType
{
	Box,
	Circle,
};

enum class PhysicsLayer
{
	Default = 0,
	Ground = 1,
	Wall = 2,
	Player = 3,
	Item = 4,
	Obstacle = 5,
	Count
};

enum class ShapeType
{
	None,
	Circle,
	Convex,
	Rectangle,
};

enum class ItemType
{
	None = -1,
	Fish,
};

enum class EnemyType
{
	None = -1,
};

enum class StageIndex
{
	None = -1,
};
#define UILayer 100
#include "AnimationClip.h"