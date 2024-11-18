#pragma once

// ���� :
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
	Rail,
	Last
};