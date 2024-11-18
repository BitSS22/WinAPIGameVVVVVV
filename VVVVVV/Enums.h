#pragma once

// Ό³Έν :
enum class ERenderOrder
{
	BACKGROUND,
	BACKGROUND_EFFECT,
	BACKGROUND_TILE,
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
	Enermy,
	Platform,
	Save,
	Last
};

enum class ETileType
{
	None,
	BackGround,
	Collision,
	Spike,
	Rail,
	Last
};