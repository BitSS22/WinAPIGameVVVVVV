#pragma once
#include "Tile.h"

// ���� :
class ACollisionTile : public ATile
{
public:
	ACollisionTile();
	~ACollisionTile();

	ACollisionTile(const ACollisionTile& _Other) = delete;
	ACollisionTile(ACollisionTile&& _Other) noexcept = delete;
	ACollisionTile& operator=(const ACollisionTile& _Other) = delete;
	ACollisionTile& operator=(ACollisionTile&& _Other) noexcept = delete;

private:

public:

private:

};

