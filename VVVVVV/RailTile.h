#pragma once
#include "AnimationTile.h"

// Ό³Έν :
class ARailTile : public AAnimationTile
{
public:
	ARailTile();
	~ARailTile();

	ARailTile(const ARailTile& _Other) = delete;
	ARailTile(ARailTile&& _Other) noexcept = delete;
	ARailTile& operator=(const ARailTile& _Other) = delete;
	ARailTile& operator=(ARailTile&& _Other) noexcept = delete;

private:

public:

private:

};

