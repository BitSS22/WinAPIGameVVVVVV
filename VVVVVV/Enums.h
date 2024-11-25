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
	Fade,
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
	Enermy,
	Platform,
	PlatformHide,
	CheckPoint,
	Teleport,
	FlipLine,
	Last
};

enum class ETileType
{
	None,
	BackGround,
	Collision,
	Spike,
	Animation,
	RailLeft,
	RailRight,
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

enum class EGameColor
{
	Cyan,
	Pink,
	Red,
	Blue,
	Yellow,
	Green,
	Grey,
	White
};

EEntityType& operator++(EEntityType& _Type);
EEntityType& operator--(EEntityType& _Type);
ETileType& operator++(ETileType& _Type);
ETileType& operator--(ETileType& _Type);
EBackGroundType& operator++(EBackGroundType& _Type);
EBackGroundType& operator--(EBackGroundType& _Type);
EGameColor& operator++(EGameColor& _Type);
EGameColor& operator--(EGameColor& _Type);
