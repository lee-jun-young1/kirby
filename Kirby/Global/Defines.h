#pragma once


enum class Languages
{
	ENG,
	COUNT,
};


enum class SceneId
{
	None = -1,
	Title,
	MapTool,
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
	Camera,
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
	Life,
	God,
	MaxTomato,
	Normal,
};

enum class EnemyType
{
	None = -1,
	Cutter,
	Beam,
	Bomb,
	Bear,
	Chick,
	Fly,
	Mushroom,
	Normal,
	SB_Bomb,
	Wood,
};

enum class StageIndex
{
	None = -1,
	GreenGreen,
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
	Null = -1,
	None = 20,
	Cutter = 0,
	Beam = 1,
	Bomb = 10,
};

enum class CameraType
{
	None = -1,
	Free,
	Horizontal,
	Vertical,
	Fixed,
	MapStart,
	MapEnd,
};

enum class GroundType
{
	None = -1,
	Normal,
	Tilted,
	Throught,
	Background,
	Crashed,
	Transpar,
};

#define UILayer 100
#include "AnimationClip.h"