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
	std::string AnimationName = {};
	FVector2D LastDir = FVector2D::RIGHT;
	FVector2D MoveValue = FVector2D::ZERO;
	static constexpr int PointCount = 5;
	FVector2D Points[static_cast<int>(EPlayerPoint::Last)][APlayer::PointCount] = {};

	bool IsSad = false;
	bool IsFlip = false;
	bool IsGround = false;
	bool IsDeath = false;

	const float Speed = 400.f;
	const float GravityForce = 400.f;
	const float DeathTime = 1.f;
	float CurDeathTime = 0.f;

	FIntPoint SaveWorldIndex = FVector2D::ZERO;
	FVector2D SaveLocation = FVector2D(320.f, 240.f);
	bool SaveFlip = false;

	bool TestTrigger = false;
	DWORD TestPrevCount = 0;
	DWORD TestCount = 0;

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
	void DeathCheck();
	void Move();
	void ReSpawn();
	void ResetData();

	void PlayerDefualtSetup();

	void Debug();

public:
	void SetDeath(bool _Value)
	{
		AGameWorld::GetRoom()->SetEntityMove(!_Value);
		IsDeath = _Value;
	}
	bool GetDeath()
	{
		return IsDeath;
	}
	void SetSad(bool _Value)
	{
		IsSad = _Value;
	}
	void SetCheckPoint(const FVector2D& _Location, bool _Flip)
	{
		SaveWorldIndex = AGameWorld::GetCurRoomIndex();
		SaveLocation = _Location;
		SaveFlip = _Flip;
	}
	FVector2D GetMoveValue() const
	{
		return MoveValue;
	}
	void SetMoveValue(const FVector2D& _Value)
	{
		MoveValue = _Value;
	}
	bool GetFlip() const
	{
		return IsFlip;
	}
	void SetFlip(bool _Value)
	{
		IsFlip = _Value;
	}
	void SetGround(bool _Value)
	{
		IsGround = _Value;
	}
};

