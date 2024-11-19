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
	Entity,
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

EEntityType& operator++(EEntityType& _Type);
EEntityType& operator--(EEntityType& _Type);
ETileType& operator++(ETileType& _Type);
ETileType& operator--(ETileType& _Type);
EBackGroundType& operator++(EBackGroundType& _Type);
EBackGroundType& operator--(EBackGroundType& _Type);