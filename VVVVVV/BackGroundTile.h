#pragma once
#include "Tile.h"

// Ό³Έν :
class ABackGroundTile : public ATile
{
public:
	ABackGroundTile();
	~ABackGroundTile();

	ABackGroundTile(const ABackGroundTile& _Other) = delete;
	ABackGroundTile(ABackGroundTile&& _Other) noexcept = delete;
	ABackGroundTile& operator=(const ABackGroundTile& _Other) = delete;
	ABackGroundTile& operator=(ABackGroundTile&& _Other) noexcept = delete;

private:

public:

private:

};

