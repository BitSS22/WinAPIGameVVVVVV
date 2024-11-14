#pragma once
#include "Entity.h"

enum class PixelPointY
{
	LeftBottom,
	Bottom,
	RightBottom,
	LAST
};

enum class PixelPointX
{
	Left1,
	Left2,
	Left3,
	Left4,
	AND,
	Right1,
	Right2,
	Right3,
	Right4,
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
	FVector2D PointsY[static_cast<int>(PixelPointY::LAST)] = {};
	FVector2D PointsX[static_cast<int>(PixelPointX::LAST)] = {};

public:
	void BeginPlay() override;
	void Tick() override;

private:

};

