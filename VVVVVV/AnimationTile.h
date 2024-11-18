#pragma once
#include "CollisionTile.h"

// Ό³Έν :
class AAnimationTile : public ACollisionTile
{
public:
	AAnimationTile();
	~AAnimationTile();

	AAnimationTile(const AAnimationTile& _Other) = delete;
	AAnimationTile(AAnimationTile&& _Other) noexcept = delete;
	AAnimationTile& operator=(const AAnimationTile& _Other) = delete;
	AAnimationTile& operator=(AAnimationTile&& _Other) noexcept = delete;

private:
	virtual void BeginPlay() override;
	virtual void Tick() override;

public:

private:

};

