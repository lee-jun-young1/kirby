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
	Ground,
	Player,
	PlayerEffect,
	Enemy,
	EnemyEffect,
	Item,
	AbilityItem,
	Interact,
	Count
};

enum class Category
{
	None = -1,
	Player,
	Item,
	Enemy,
	Door,
	Ground,
	AmbientObject,
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

enum class DoorType
{
	None = -1,
	OneWay,
	TwoWay,
	WarpStar,
};

enum class KirbyAbility
{
	None,
	Cutter,
	Beam,
	Bomb,
};

enum class CameraType
{
	None = -1,
	Free,
	Horizontal,
	Vertical,
	Fixed
};
#define UILayer 100
#include "AnimationClip.h"