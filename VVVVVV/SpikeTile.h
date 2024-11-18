#pragma once
#include "CollisionTile.h"

// Ό³Έν :
class ASpikeTile : public ACollisionTile
{
public:
	ASpikeTile();
	~ASpikeTile();

	ASpikeTile(const ASpikeTile& _Other) = delete;
	ASpikeTile(ASpikeTile&& _Other) noexcept = delete;
	ASpikeTile& operator=(const ASpikeTile& _Other) = delete;
	ASpikeTile& operator=(ASpikeTile&& _Other) noexcept = delete;

private:

public:

private:

};

