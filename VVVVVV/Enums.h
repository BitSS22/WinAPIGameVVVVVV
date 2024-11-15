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
	EDITOR_CURSOR
};

enum class ECollisionGroup
{
	Player,
	Enermy,
	Platform,
	Save
};

enum class EColorType
{
	WHITE,
	CYAN,
	PINK,
	RED,
	BLUE,
	YELLOW,
	GREEN,
	GREY,
	SIZE
};
