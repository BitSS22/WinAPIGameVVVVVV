#pragma once

// Ό³Έν :
enum class ERenderOrder
{
	BACKGROUND,
	BACKGROUND_EFFECT,
	TILE,
	Entity,
	FRIEND,
	PLAYER,
	EDITOR_CURSOR,
	Last
};

enum class ECollisionGroup
{
	Player,
	Enermy,
	Platform,
	Save,
	Last
};

enum class EEntityType
{
	Guy,
	Player,
	Enermy,
	Platform,
	CheckPoint,
	Teleport,
	Last
};

enum class ETileType
{
	None,
	BackGround,
	Collision,
	Spike,
	Animation,
	Rail,
	Last
};

enum class EBackGroundType
{
	Space,
	Horizontal,
	Vertical,
	Tower,
	Ending,
	Last
};
