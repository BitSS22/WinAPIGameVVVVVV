#pragma once
#include "Entity.h"
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include "Guy.h"

enum class EPlayerState
{
	Idle,
	Move,
	Death,
	LAST
};

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	U2DCollision* Collider = nullptr;
	UFSMStateManager FSM = {};
	std::string AnimationName = {};
	FVector2D LastDir = FVector2D::RIGHT;
	FVector2D MoveValue = FVector2D::ZERO;
	bool IsSad = false;
	bool IsFlip = false;
	bool OnGround = false;
	bool IsDeath = false;
	const float Speed = 500.f;
	const float GravityForce = 600.f;
	const float DeathTime = 1.f;
	float CurDeathTime = 0.f;

public:
	void BeginPlay() override;
	void Tick() override;

private:
	void Idle();
	void Move();
	void Death();

	void SetAnimation();
	void Gravity();
	void FlipCheck();
	void TileCheck();
	void KeyCheck();
	void MoveRoomCheck();
	void DeathCheck();
	void Reset();

};

