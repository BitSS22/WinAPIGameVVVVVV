#pragma once
#include "Entity.h"
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class State
{
	WalkLeft,
	WalkRight,
	FlipWalkLeft,
	FlipWalkRight,
	IdleLeft,
	IdleRight,
	FlipIdleLeft,
	FlipIdleRight,
	LAST
};

enum class PixelPointY
{
	LeftBottom,
	Bottom,
	RightBottom,
	LeftTop,
	Top,
	RightTop,
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
	bool IsFlip = false;
	bool OnGround = false;
	float GravitySpeed = 600.f;
	FVector2D PointsY[static_cast<int>(PixelPointY::LAST)] = {};
	FVector2D PointsX[static_cast<int>(PixelPointX::LAST)] = {};
	FVector2D MoveValue = {};
	FVector2D LastKey = FVector2D::RIGHT;
	FIntPoint SaveWorldIndex = {};
	FVector2D SaveLocation = {};
	U2DCollision* Collider = nullptr;
	float DeathTime = 2.f;
	bool IsDeath = false;

public:
	void BeginPlay() override;
	void Tick() override;

private:
	void Move();
	void Flip();
	void MoveRoom();
	void SetCollisionPoint();
	void Reset();

	void CollisionPlatform();
	void CollisionEnermy();
	void CollisionSave();

};

