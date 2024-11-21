#pragma once
#include "Entity.h"
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include "Guy.h"

enum class EPlayerPoint
{
	Left,
	Right,
	Top,
	Bottom,
	Last
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
	std::string AnimationName = {};
	FVector2D LastDir = FVector2D::RIGHT;
	FVector2D MoveValue = FVector2D::ZERO;
	static constexpr int PointCount = 5;
	FVector2D Points[static_cast<int>(EPlayerPoint::Last)][APlayer::PointCount] = {};
	bool IsSad = true;
	bool IsFlip = false;
	bool IsGround = false;
	bool IsDeath = false;
	const float Speed = 500.f;
	const float GravityForce = 600.f;//600.f;
	const float DeathTime = 1.f;
	float CurDeathTime = 0.f;
	FVector2D SaveWorldIndex = FVector2D::ZERO;
	FVector2D SaveLocation = FVector2D::ZERO;

public:
	void BeginPlay() override;
	void Tick() override;

private:
	void Input();
	void AnimationChange();
	void Gravity();
	void Death();
	void EntityCollisionCheck();
	void TileCheck();
	void MoveRoomCheck();
	void ReSpawn();
	void ResetData();

	void PlayerDefualtSetup();

	void Debug();

public:
	void SetDeath(bool _Value)
	{
		IsDeath = _Value;
	}
	void SetGround(bool _Value)
	{
		IsGround = _Value;
	}
	void SetFlip(bool _Value)
	{
		IsFlip = _Value;
	}
	void SetSad(bool _Value)
	{
		IsSad = _Value;
	}

};

