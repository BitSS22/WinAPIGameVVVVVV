#pragma once
#include "Entity.h"

enum class PixelPoint
{
	LeftTop,
	RightTop,
	LeftBottom,
	RightBottom,
	LAST
};

class USpriteRenderer;

class APlayer : public AEntity
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

private:
	float Speed = 500.f;
	bool Flip = false;
	bool OnGround = false;
	float GravitySpeed = 500.f;
	FVector2D Points[static_cast<int>(PixelPoint::LAST)] = {};

public:
	void BeginPlay() override;
	void Tick() override;

private:

};

